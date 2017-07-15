#include "DJuliaSet.h"

//-------------------------------------
void DJuliaSet::update(float delta)
{
	CHECK_START();

	_radin += _radinV * delta;
	if (_radin >= TWO_PI)
	{
		_radin -= TWO_PI;
	}

	drawJuliaSet(
		_display.getPixelsRef()
		, cos(_radin) * 0.7885
		, sin(_radin) * 0.7885
	);
	_display.update();
}

//-------------------------------------
void DJuliaSet::draw(int x, int y, int w, int h)
{
	CHECK_START();
	ofPushStyle();
	ofSetColor(255);
	{
		_display.draw(w * -0.5, h * -0.5, w, h);
	}
	ofPopStyle();
}

//-------------------------------------
void DJuliaSet::start()
{
	_isStart = true;

	_display.clear();
	_display.allocate(cDJSCanvasWidth, cDJSCanvasHeight, ofImageType::OF_IMAGE_COLOR);

	_radinV = PI * 0.5;
	_radin = 0;
	drawJuliaSet(
		_display.getPixelsRef()
		, cos(_radin) * 0.7885
		, sin(_radin) * 0.7885
	);
	_display.update();
}

//-------------------------------------
void DJuliaSet::stop()
{
	_isStart = false;

}

//-------------------------------------
void DJuliaSet::drawJuliaSet(ofPixelsRef pix, double real, double imaginary)
{
	int histogram[cDJSMaximunCheck] = { 0 };
	ofColor pattern[cDJSMaximunCheck];


	double diffR = (cDJSRealPartRange.second - cDJSRealPartRange.first) / cDJSCanvasWidth;
	double diffI = (cDJSImaginePartRange.second - cDJSImaginePartRange.first) / cDJSCanvasHeight;
	for (int y = 0; y < cDJSCanvasHeight; y++)
	{
		for (int x = 0; x < cDJSCanvasWidth; x++)
		{
			int index = (x + y * cDJSCanvasWidth) * 3;
			double r, i;
			double temp;

			r = cDJSRealPartRange.first + diffR * x;
			i = cDJSImaginePartRange.first + diffI * y;
			int n = 0;
			while (n < cDJSMaximunCheck && (r * r + i * i) < 4)
			{
				temp = r*r - i*i + real;
				i = 2 * r * i + imaginary;
				r = temp;
				n++;
			}

			if (n == cDJSMaximunCheck)
			{
				_iterMat[y][x] = n - 1;
				histogram[n - 1]++;
			}
			else
			{
				_iterMat[y][x] = n;
				histogram[n]++;
			}
		}
	}

	//Create color pattern
	float total = cDJSCanvasHeight * cDJSCanvasWidth;
	int counter = 0;
	ofColor c(220, 50, 50);
	for (int i = 0; i < cDJSMaximunCheck; i++)
	{
		counter += histogram[i];
		float hueAngle = 90 + (counter / total) * 360;
		c.setHueAngle(hueAngle);
		pattern[i].set(c);
	}
	pattern[cDJSMaximunCheck - 1].set(0, 0, 0);

	//Render color
	for (int y = 0; y < cDJSCanvasHeight; y++)
	{
		for (int x = 0; x < cDJSCanvasWidth; x++)
		{
			int index = (x + y * cDJSCanvasWidth) * 3;

			pix[index] = pattern[_iterMat[y][x]].r;
			pix[index + 1] = pattern[_iterMat[y][x]].g;
			pix[index + 2] = pattern[_iterMat[y][x]].b;
		}
	}

}