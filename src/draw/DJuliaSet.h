#pragma once

#include "DBase.h"

class DJuliaSet : public DBase
{
public:
	DJuliaSet();

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;
	void trigger() override;
private:
	void init();
	void initShader();
	void drawJuliaSet(ofPixelsRef pix, double real, double imaginary);
	void drawJuliaSetShader(ofPixelsRef pix, double real, double imaginary);
	void initPattern();

private:
	ofImage _display;
	float _radin, _radinV;
	float _radinDeltaR, _radinDeltaI;
	float _deltaR, _deltaI;
	int _iterMat[cDJSCanvasHeight][cDJSCanvasWidth];

	//Shader
	ofShader _julia;
	ofImage _temp;
	ofImage _pattern;
	ofFbo _canvas;
};