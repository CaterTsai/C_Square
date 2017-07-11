#include "DMandelbrotSet.h"

//-------------------------------------
void DMandelbrotSet::update(float delta)
{
	CHECK_START();

	_timer -= delta;
	if (_timer < 0.0)
	{
		cout << _zoomScale << endl;
		if (_zoomScale < 10000000.0)
		{
			//_zoomScale += _zoomVal * delta;
			_zoomScale *= 2;
			double p = 1.0 / _zoomScale;
			double rMin = _zoomCenter.x - _distRMin * p;
			double rMax = _zoomCenter.x + _distRMax * p;
			double iMin = _zoomCenter.y - _distIMin * p;
			double iMax = _zoomCenter.y + _distIMax * p;

			drawMandelbrot(_display.getPixelsRef(), rMin, rMax, iMin, iMax);
			_display.update();
		}
		_timer = _zoomTime;
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
	_timer = _zoomTime;

	_display.clear();
	_display.allocate(cDMSCanvasWidth, cDMSCanvasHeight, ofImageType::OF_IMAGE_COLOR);
	_zoomScale = 1.0f;
	_zoomVal = 100.0f;
	_zoomCenter.x = -0.1011;//ofRandom(cDMRealPartRange.first, cDMRealPartRange.second);
	_zoomCenter.y = 0.9563;
	
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
}

//-------------------------------------
void DMandelbrotSet::stop()
{
	_isStart = false;

}

//-------------------------------------
void DMandelbrotSet::drawMandelbrot(ofPixelsRef pix, double rmin, double rmax, double imin, double imax)
{
	double diffR = (rmax - rmin) / cDMSCanvasWidth;
	double diffI = (imax - imin) / cDMSCanvasHeight;
	for (int y = 0; y < cDMSCanvasHeight; y++)
	{
		for (int x = 0; x < cDMSCanvasWidth; x++)
		{
			int index = (x + y * cDMSCanvasWidth) * 3;
			double r0, r, i0, i;
			double temp;

			r0 = rmin + diffR * x;
			i0 = imin + diffI * y;
			r = 0;
			i = 0;
			int n = 0;
			while (n < cDMSMaximunCheck && (r * r + i * i) < 4)
			{
				temp = r*r - i*i + r0;
				i = 2 * r * i + i0;
				r = temp;
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