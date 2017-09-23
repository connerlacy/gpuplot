#pragma once

#include "cinder/app/cocoa/AppCocoaView.h"
#include "cinder/osc/Osc.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cinder;

#define USE_UDP 1

#if USE_UDP
using Receiver = osc::ReceiverUdp;
using protocol = asio::ip::udp;
#else
using Receiver = osc::ReceiverTcp;
using protocol = asio::ip::tcp;
#endif

const uint16_t localPort = 9999;

class Graph
{
public:
    Graph();
    Graph(int index);
    void init();
    void draw();
    void setValue(float v);
    Graph setPos(vec2 pos);
    Graph setSize(vec2 dim);
    void setIndex(int i);
    int  getIndex();
    void resize();
    gl::BatchRef		batch;
    gl::TextureRef		texture;
    gl::GlslProgRef		glsl;
    geom::Rect          rect;
    std::list<float>    fifo;
    std::vector<float>  buf;
    vec2 pos;
    vec2 size;
    int index;
};

class gpuplotApp : public cinder::app::AppCocoaView {
  public:
    gpuplotApp();
	void setup() override;
    void update() override;
    void draw() override;

    Receiver 	receiver;
    
    std::vector<Graph> graphs;
    std::list<float> vals;
};
