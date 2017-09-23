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
    mApp->console() << "text changed\n";
}

@end
