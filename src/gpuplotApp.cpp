#include "gpuplotApp.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;



Graph::Graph() : index(-1)
{
    init();
}

Graph::Graph(int indx) : index(indx)
{
    init();
}

void Graph::init()
{
    glsl  = gl::GlslProg::create( loadResource( "shader.vert" ), loadResource( "shader.frag" ) );
    //glsl->bind();
    //batch = gl::Batch::create( geom::Rect().rect(Area(0,0,500,500)), glsl );
    //mGlsl->bind();
    for(int i =0; i < PLOT_NUM_POINTS; i++) { fifo.push_back(i); buf.push_back(i); }
}

void Graph::setValue(float v)
{
    fifo.push_back(v);
    fifo.pop_front();
    
    buf.clear();
    
    for(auto i : fifo) { buf.push_back(i * 0.5 + 0.5); }
}

void Graph::setIndex(int i)
{
    index = i;
}

int Graph::getIndex()
{
    return index;
}

Graph Graph::setPos(vec2 p)
{
    pos = p;
    
    return *this;
}

Graph Graph::setSize(vec2 s)
{
    size = s;
    
    return *this;
}

void Graph::draw()
{
    //gl::ScopedGlslProg s(glsl);
    glsl->bind();
    glsl->uniform("utime", (float)getElapsedSeconds());
    glsl->uniform("uVal", buf.data(), PLOT_NUM_POINTS);
    //batch->draw();
    
    gl::drawSolidRect(Rectf(pos, pos + size));
}

gpuplotApp::gpuplotApp() : receiver(localPort)
{
}

void gpuplotApp::setGraphAddress(int graphIndex, std::string address)
{
    addresses[graphIndex] = address;
}

void gpuplotApp::oscParse(const osc::Message &msg)
{
    int i = 0;
    for(auto a : addresses)
    {
        if(a == msg.getAddress())
        {
            graphs[i].setValue(msg[0].flt());
            break;
        }
        i++;
    }
}

void gpuplotApp::setup()
{
    for(int i =0; i < 4; i++)
    {
        graphs.push_back(Graph(i));
        addresses.push_back("/graph" + std::to_string(i));
        //setGraphAddress(i, addresses.back());
    }
    
    try {
        // Bind the receiver to the endpoint. This function may throw.
        receiver.bind();
    }
    catch( const osc::Exception &ex ) {
        console() << ex.what();
        quit();
    }
    
    receiver.listen(
                    []( asio::error_code error, protocol::endpoint endpoint ) -> bool {
                        if( error ) {
                            return false;
                        }
                        else
                            return true;
                    });
    
    receiver.setListener( "*", std::bind(&gpuplotApp::oscParse, this, std::placeholders::_1));
}

void gpuplotApp::update()
{
    vec2 colRow(1,4);
    vec2 graphSize = (vec2)getWindowSize()/colRow;
    
    int j =0;
    for(auto g : graphs)
    {
        vec2 pos(fmod(j, 1) * graphSize.x, j/1 * graphSize.y);
        //int x = ;
        graphs[j].setPos(pos + graphSize*0.025f);
        graphs[j].setSize(graphSize * 0.95f);
        j++;
    }
}

void gpuplotApp::draw()
{
    gl::clear( Color( 1, 1, 1 ) );
    
    for(auto g : graphs)
    {
        g.draw();
    }
}
