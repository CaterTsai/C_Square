#pragma once

#include "DBase.h"

class DMandelbrotSet : public DBase
{
public:
	DMandelbrotSet()
		:DBase(eDMandelbrotSet)
		, _zoomTime(1.0)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void drawMandelbrotHistogram(ofPixelsRef pix, double rmin, double rmax, double imin, double imax);
	void drawMandelbrotSmooth(ofPixelsRef pix, double rmin, double rmax, double imin, double imax);

private:
	float _zoomTime;
	ofImage _display;
	ofVec2f _zoomCenter;
	double _distRMin, _distRMax, _distIMin, _distIMax;
	double _zoomScale, _zoomVal;

	int _iterMat[cDMSCanvasHeight][cDMSCanvasWidth];
	float _pMat[cDMSCanvasHeight][cDMSCanvasWidth];
};