#pragma once

#include "cinder/app/cocoa/AppCocoaView.h"

class gpuplotApp : public cinder::app::AppCocoaView {
  public:
	void				setup();
	void				draw();

	float				mRadius;
	cinder::Colorf		mColor;
};
