
#include "cinder/app/cocoa/CinderViewMac.h"
#include "gpuplotApp.h"
#include "cinder/app/RendererGl.h"
#import <Cocoa/Cocoa.h>

@interface gpuplotDelegate : NSObject <NSApplicationDelegate>
{
	IBOutlet CinderViewMac	*cinderView;
	IBOutlet NSWindow		*window;
	IBOutlet NSColorWell	*colorWell;

	gpuplotApp		*mApp;
}

@property (assign) IBOutlet NSWindow *window;

- (IBAction)subdivisionSliderChanged:(id)sender;
- (IBAction)colorChanged:(id)sender;

@end
