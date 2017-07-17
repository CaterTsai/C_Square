#include "DMandelbrotSet.h"

//-------------------------------------
DMandelbrotSet::DMandelbrotSet()
	:DBase(eDMandelbrotSet)
	, _zoomTime(1.0)
{
	if (ofIsGLProgrammableRenderer()) {
		//string 
		_mandelbrot.load("MandelbrotSet/shadersGL3/mandelbrot");
	}
	else {
		_mandelbrot.load("MandelbrotSet/shadersGL2/mandelbrot");
	}
}

//-------------------------------------
void DMandelbrotSet::update(float delta)
{
	CHECK_START();

	_timer -= delta;

	if (_zoomScale < 10000.0)
	{
		//_zoomScale += _zoomVal * delta;
		_zoomScale *= 1.05;
		double p = 1.0 / _zoomScale;
		double rMin = _zoomCenter.x - _distRMin * p;
		double rMax = _zoomCenter.x + _distRMax * p;
		double iMin = _zoomCenter.y - _distIMin * p;
		double iMax = _zoomCenter.y + _distIMax * p;

		drawMandelbrotShader(_display.getPixelsRef(), rMin, rMax, iMin, iMax);
		_display.update();
	}
	_timer = _zoomTime;

}

//-------------------------------------
void DMandelbrotSet::draw(int x, int y, int w, int h)
{
	CHECK_START();
	ofPushStyle();
	ofSetColor(255);
	{
		_display.draw(w * -0.5, h * -0.5, w, h);
		//_pattern.draw(0, 0, 100, 100);
	}
	ofPopStyle();

}

//-------------------------------------
void DMandelbrotSet::start()
{
	_isStart = true;

	_timer = _zoomTime;
	_zoomScale = 1.0f;
	_zoomVal = 100.0f;
	//_zoomCenter.x = -0.1011;//ofRandom(cDMSRealPartRange.first, cDMSRealPartRange.second);
	//_zoomCenter.y = 0.9563;
	_zoomCenter.x = 0.28693186889504513;
	_zoomCenter.y = 0.014286693904085048;

	_distRMin = abs(cDMSRealPartRange.first - _zoomCenter.x);
	_distRMax = abs(cDMSRealPartRange.second - _zoomCenter.x);
	_distIMin = abs(cDMSImaginePartRange.first - _zoomCenter.y);
	_distIMax = abs(cDMSImaginePartRange.second - _zoomCenter.y);

	_display.clear();
	_display.allocate(cDMSCanvasWidth, cDMSCanvasHeight, ofImageType::OF_IMAGE_COLOR);

	initShader();
	
}

//-------------------------------------
void DMandelbrotSet::stop()
{
	_isStart = false;

}

//-------------------------------------
void DMandelbrotSet::init()
{
	double p = 1.0 / _zoomScale;
	double rMin = _zoomCenter.x - _distRMin * p;
	double rMax = _zoomCenter.x + _distRMax * p;
	double iMin = _zoomCenter.y - _distIMin * p;
	double iMax = _zoomCenter.y + _distIMax * p;

	drawMandelbrotSmooth(
		_display.getPixelsRef()
		,rMin
		,rMax
		,iMin
		,iMax
	);
	_display.update();
}

//-------------------------------------
void DMandelbrotSet::initShader()
{
	if (!_mandelbrot.isLoaded())
	{
		ofLog(OF_LOG_ERROR, "[DMandelbrotSet::initShader]Load shader failed");
		return;
	}
	
	initPattern();

	_canvas.allocate(cDMSCanvasWidth, cDMSCanvasHeight, GL_RGB);
	_temp.allocate(cDMSCanvasWidth, cDMSCanvasHeight, ofImageType::OF_IMAGE_COLOR);

	double p = 1.0 / _zoomScale;
	double rMin = _zoomCenter.x - _distRMin * p;
	double rMax = _zoomCenter.x + _distRMax * p;
	double iMin = _zoomCenter.y - _distIMin * p;
	double iMax = _zoomCenter.y + _distIMax * p;
	drawMandelbrotShader(
		_display.getPixelsRef()
		, rMin
		, rMax
		, iMin
		, iMax
	);
	_display.update();

	
}

//-------------------------------------
void DMandelbrotSet::initPattern()
{
	_pattern.clear();
	_pattern.allocate(cDMSMaximunCheck, 1, ofImageType::OF_IMAGE_COLOR);
	ofPixelsRef pix = _pattern.getPixelsRef();

	vector<ofColor> colorSeed;
	colorSeed.resize(cDMSColorPatternNum);
	ofColor c(50, 200, 50);
	float angle = c.getHueAngle();
	angle += ofRandom(-180, 180);
	c.setHueAngle(angle);
	for (int i = 0; i < cDMSColorPatternNum; i++)
	{	
		colorSeed[i] = c;
		angle += ofRandom(45, 90);
		c.setHueAngle(angle);		
	}

	int diff = static_cast<int>((float)cDMSMaximunCheck / (cDMSColorPatternNum - 1));
	for (int i = 1; i < cDMSColorPatternNum; i++)
	{
		int s = (i - 1) * diff;
		int e = i * diff;
		
		for (int j = 0; j < diff; j++)
		{
			if (s + j >= e)
			{
				break;
			}
			auto color = colorSeed[i - 1].getLerped(colorSeed[i], (float)j / diff);

			pix[(s + j) * 3] = color.r;
			pix[(s + j) * 3 + 1] = color.g;
			pix[(s + j) * 3 + 2] = color.b;
		}
	}

	_pattern.update();
}

//-------------------------------------
void DMandelbrotSet::drawMandelbrotHistogram(ofPixelsRef pix, double rmin, double rmax, double imin, double imax)
{
	int histogram[cDMSMaximunCheck] = {0};
	ofColor pattern[cDMSMaximunCheck];
	
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
			_iterMat[y][x] = n - 1;
			histogram[n - 1]++;
		}
	}

	//Create color pattern
	float total = cDMSCanvasHeight * cDMSCanvasWidth;
	int counter = 0;
	ofColor c(255, 0, 0);
	for (int i = 0; i < cDMSMaximunCheck; i++)
	{
		counter += histogram[i];
		float hueAngle = 90 + (counter / total) * 180;
		c.setHueAngle(hueAngle);
		pattern[i].set(c);
	}
	pattern[cDMSMaximunCheck - 1].set(0, 0, 0);

	//Render color
	for (int y = 0; y < cDMSCanvasHeight; y++)
	{
		for (int x = 0; x < cDMSCanvasWidth; x++)
		{
			int index = (x + y * cDMSCanvasWidth) * 3;

			pix[index] = pattern[_iterMat[y][x]].r;
			pix[index + 1] = pattern[_iterMat[y][x]].g;
			pix[index + 2] = pattern[_iterMat[y][x]].b;
		}
	}
}

//-------------------------------------
void DMandelbrotSet::drawMandelbrotSmooth(ofPixelsRef pix, double rmin, double rmax, double imin, double imax)
{
	ofColor pattern[cDMSMaximunCheck];
	int histogram[cDMSMaximunCheck] = { 0 };

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
			int iter = 0;
			ofColor c, c2;
			while (n < cDMSMaximunCheck && (r * r + i * i) < (1 << 4))
			{
				temp = r*r - i*i + r0;
				i = 2 * r * i + i0;
				r = temp;
				n++;
			}
			if (n < cDMSMaximunCheck)
			{
				double logZn = log(sqrt(r*r + i*i));
				double nu = log(logZn / log(2)) / log(2);
				//double nu = log(logZn)/log(2);
				iter = floor(n + 1 - nu);
				_pMat[y][x] = (n + 1 - nu) - iter;
			}
			else
			{
				iter = n;
				_pMat[y][x] = 0.0;
			}
			_iterMat[y][x] = iter - 1;
			histogram[iter - 1]++;
		}
	}

	//Create color pattern
	float total = cDMSCanvasHeight * cDMSCanvasWidth;
	int counter = 0;
	ofColor c(255, 0, 0);
	for (int i = 0; i < cDMSMaximunCheck; i++)
	{
		counter += histogram[i];
		float hueAngle = 180 + (counter / total) * 180;
		c.setHueAngle(hueAngle);
		pattern[i].set(c);
	}
	pattern[cDMSMaximunCheck - 1].set(0, 0, 0);

	//Render color
	for (int y = 0; y < cDMSCanvasHeight; y++)
	{
		for (int x = 0; x < cDMSCanvasWidth; x++)
		{
			int index = (x + y * cDMSCanvasWidth) * 3;

			ofColor c, c2;
			if (_iterMat[y][x] == cDMSMaximunCheck - 1)
			{
				c = pattern[_iterMat[y][x]];
			}
			else
			{
				c = pattern[_iterMat[y][x]];
				c2 = pattern[_iterMat[y][x] + 1];
				c.lerp(c2, _pMat[y][x]);
			}

			pix[index] = c.r;
			pix[index + 1] = c.g;
			pix[index + 2] = c.b;
		}
	}

}

//-------------------------------------
void DMandelbrotSet::drawMandelbrotShader(ofPixelsRef pix, double rmin, double rmax, double imin, double imax)
{
	_canvas.begin();
	ofClear(0);
	ofSetColor(255);
	_mandelbrot.begin();
	_mandelbrot.setUniformTexture("pattern", _pattern, 1);
	_mandelbrot.setUniform1f("width", cDMSCanvasWidth);
	_mandelbrot.setUniform1f("height", cDMSCanvasHeight);
	_mandelbrot.setUniform1f("rmin", rmin);
	_mandelbrot.setUniform1f("rmax", rmax);
	_mandelbrot.setUniform1f("imin", imin);
	_mandelbrot.setUniform1f("imax", imax);
	_mandelbrot.setUniform1i("iterMax", cDMSMaximunCheck);
	{
		_temp.draw(0, 0);
	}
	_mandelbrot.end();
	_canvas.end();

	_canvas.readToPixels(pix);
}
