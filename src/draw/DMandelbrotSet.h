#pragma once

#include "DBase.h"

class DMandelbrotSet : public DBase
{
public:
	DMandelbrotSet()
		:DBase(eDMandelbrotSet)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void drawMandelbrot(ofPixelsRef pix, float rmin, float rmax, float imin, float imax);


private:
	ofImage _display;
	ofVec2f _zoomCenter;
	float _distRMin, _distRMax, _distIMin, _distIMax;
	float _zoomScale, _zoomVal;
};