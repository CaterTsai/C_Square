#pragma once

#include "DBase.h"

class DMandelbrotSet : public DBase
{
public:
	DMandelbrotSet();

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void init();
	void initShader();
	void drawMandelbrotHistogram(ofPixelsRef pix, double rmin, double rmax, double imin, double imax);
	void drawMandelbrotSmooth(ofPixelsRef pix, double rmin, double rmax, double imin, double imax);
	void drawMandelbrotShader(ofPixelsRef pix, double rmin, double rmax, double imin, double imax);
private:
	ofShader _mandelbrot;
	float _zoomTime;
	ofImage _display;
	ofVec2f _zoomCenter;
	double _distRMin, _distRMax, _distIMin, _distIMax;
	double _zoomScale, _zoomVal;

	int _iterMat[cDMSCanvasHeight][cDMSCanvasWidth];
	float _pMat[cDMSCanvasHeight][cDMSCanvasWidth];

	ofImage _temp;
	ofFbo _canvas;
};