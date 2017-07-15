#pragma once

#include "DBase.h"

class DJuliaSet : public DBase
{
public:
	DJuliaSet()
		:DBase(eDJuliaSet)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void drawJuliaSet(ofPixelsRef pix, double real, double imaginary);


private:
	ofImage _display;
	float _radin, _radinV;
	int _iterMat[cDJSCanvasHeight][cDJSCanvasWidth];
};