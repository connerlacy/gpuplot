#include "cinder/Cinder.h"
#include "cinder/Rand.h"
#import "gpuplotDelegate.h"

@implementation gpuplotDelegate

@synthesize window;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	cinder::app::AppBase::Settings settings;
	cinder::app::RendererRef renderer( new cinder::app::RendererGl );
	gpuplotApp::initialize(&settings, renderer);

	mApp = new gpuplotApp;
	mApp->setupCinderView( cinderView );
	mApp->launch();

	[window setAcceptsMouseMovedEvents:YES];
}

- (IBAction)textEditChanged:(id)sender
{
    static bool oneshot = false;
    
    if(!oneshot){ oneshot = true; return;}
    mApp->setGraphAddress([sender tag], std::string([[(NSTextField*)sender stringValue] UTF8String]));
}

@end
