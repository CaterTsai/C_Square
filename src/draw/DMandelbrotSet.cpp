#include "DMandelbrotSet.h"

//-------------------------------------
void DMandelbrotSet::update(float delta)
{
	CHECK_START();

	if (_zoomScale < 500.0f)
	{
		_zoomScale += _zoomVal * delta;
		//_zoomScale *= 2;
		float p = 1.0 / _zoomScale;
		float rMin = _zoomCenter.x - _distRMin * p;
		float rMax = _zoomCenter.x + _distRMax * p;
		float iMin = _zoomCenter.y - _distIMin * p;
		float iMax = _zoomCenter.y + _distIMax * p;

		drawMandelbrot(_display.getPixelsRef(), rMin, rMax, iMin, iMax);
		_display.update();
	}

	
}

//-------------------------------------
void DMandelbrotSet::draw(int x, int y, int w, int h)
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
void DMandelbrotSet::start()
{
	_isStart = true;
	//_pix.allocate(cDMSCanvasWidth, cDMSCanvasHeight, ofImageType::OF_IMAGE_COLOR);
	_display.clear();
	_display.allocate(cDMSCanvasWidth, cDMSCanvasHeight, ofImageType::OF_IMAGE_COLOR);
	_zoomScale = 1.0f;
	_zoomVal = 100.0f;
	_zoomCenter.x = 0.26;//ofRandom(cDMRealPartRange.first, cDMRealPartRange.second);
	_zoomCenter.y = 0;
	
	_distRMin = abs(cDMRealPartRange.first - _zoomCenter.x);
	_distRMax = abs(cDMRealPartRange.second - _zoomCenter.x);
	_distIMin = abs(cDMImaginePartRange.first - _zoomCenter.y);
	_distIMax = abs(cDMImaginePartRange.second - _zoomCenter.y);

	drawMandelbrot(
		_display.getPixelsRef()
		,cDMRealPartRange.first
		, cDMRealPartRange.second
		, cDMImaginePartRange.first
		, cDMImaginePartRange.second
	);
	_display.update();
	//_display.setFromPixels(_pix);
}

//-------------------------------------
void DMandelbrotSet::stop()
{
	_isStart = false;

}

//-------------------------------------
void DMandelbrotSet::drawMandelbrot(ofPixelsRef pix, float rmin, float rmax, float imin, float imax)
{
	double diffR = (rmax - rmin) / cDMSCanvasWidth;
	double diffI = (imax - imin) / cDMSCanvasHeight;
	for (int y = 0; y < cDMSCanvasHeight; y++)
	{
		for (int x = 0; x < cDMSCanvasWidth; x++)
		{
			int index = (x + y * cDMSCanvasWidth) * 3;
			double rValS, rVal;
			rValS = rVal = rmin + diffR * x;
			double iValS, iVal;
			iValS = iVal = imin + diffI * y;

			int n = 0;
			while (n < cDMSMaximunCheck)
			{
				double r = rVal * rVal - iVal * iVal;
				double i = 2 * rVal * iVal;
				rVal = r + rValS;
				iVal = i + iValS;
				if (abs(rVal + iVal) > 16)
				{
					break;
				}
				n++;
			}

			double gray = ofMap(n, 0, cDMSMaximunCheck, 0, 1);
			gray = ofMap(sqrt(gray), 0, 1, 0, 255);
			if (n == cDMSMaximunCheck)
			{
				gray = 0;
			}
			pix[index] = gray;
			pix[index + 1] = gray;
			pix[index + 2] = gray;
		}
	}
}