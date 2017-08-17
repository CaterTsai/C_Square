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
	//void init();
	void initShader();
	void initPattern();
	void initCenter();
	//void drawMandelbrotHistogram(ofPixelsRef pix, double rmin, double rmax, double imin, double imax);
	//void drawMandelbrotSmooth(ofPixelsRef pix, double rmin, double rmax, double imin, double imax);
	void drawMandelbrotShader(ofPixelsRef pix, double rmin, double rmax, double imin, double imax);
private:
	ofImage _display;
	ofVec2f _zoomCenter;
	ofVec2f _zoomCenterSet[cDMSCenterNum];
	int _centerId = 0;
	double _distRMin, _distRMax, _distIMin, _distIMax;
	double _zoomScale, _zoomV;

	//int _iterMat[cDMSCanvasHeight][cDMSCanvasWidth];
	//float _pMat[cDMSCanvasHeight][cDMSCanvasWidth];

	//Shader
	ofShader _mandelbrot;
	ofImage _temp;
	ofImage _pattern;
	ofFbo _canvas;
};