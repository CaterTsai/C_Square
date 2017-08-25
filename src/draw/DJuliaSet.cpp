#include "DJuliaSet.h"

//-------------------------------------
DJuliaSet::DJuliaSet()
	:DBase(eDJuliaSet)
{
	if (ofIsGLProgrammableRenderer()) {
		//string 
		_julia.load("JuliaSet/shadersGL3/julia");
	}
	else {
		_julia.load("JuliaSet/shadersGL2/julia");
	}
}

//-------------------------------------
void DJuliaSet::update(float delta)
{
	CHECK_START();

	_radin += _radinV * delta;
	if (_radin >= TWO_PI)
	{
		_radin -= TWO_PI;
	}

	drawJuliaSetShader(
		_display.getPixelsRef()
		, cos(_radin * _radinDeltaR) * _deltaR
		, sin(_radin * _radinDeltaI) * _deltaI
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

	_radinV = PI * 0.2;
	_radin = 0;
	_radinDeltaI = ofRandom(0.2, 4);
	_radinDeltaR = ofRandom(0.2, 4);
	_deltaR = ofRandom(-1, 1);
	_deltaI = ofRandom(-1, 1);

	initShader();
	
}

//-------------------------------------
void DJuliaSet::stop()
{
	_isStart = false;
	
}

//-------------------------------------
void DJuliaSet::trigger()
{
	_radinDeltaI = ofRandom(0.2, 4);
	_radinDeltaR = ofRandom(0.2, 4);
	_deltaR = ofRandom(-1, 1);
	_deltaI = ofRandom(-1, 1);
	initPattern();
}

//-------------------------------------
void DJuliaSet::init()
{
	drawJuliaSet(
		_display.getPixelsRef()
		, cos(_radin * _radinDeltaR) * _deltaR
		, sin(_radin * _radinDeltaI) * _deltaI
	);
	_display.update();
}

//-------------------------------------
void DJuliaSet::initShader()
{
	if (!_julia.isLoaded())
	{
		ofLog(OF_LOG_ERROR, "[DJuliaSet::initShader::initShader]Load shader failed");
		return;
	}

	initPattern();
	_canvas.clear();
	_temp.clear();
	_canvas.allocate(cDJSCanvasWidth, cDJSCanvasHeight, GL_RGB);
	_temp.allocate(cDJSCanvasWidth, cDJSCanvasHeight, ofImageType::OF_IMAGE_COLOR);


	drawJuliaSetShader(
		_display.getPixelsRef()
		, cos(_radin * _radinDeltaR) * _deltaR
		, sin(_radin * _radinDeltaI) * _deltaI
	);
	_display.update();
}

//-------------------------------------
void DJuliaSet::initPattern()
{
	_pattern.clear();
	_pattern.allocate(cDJSMaximunCheck, 1, ofImageType::OF_IMAGE_COLOR);
	ofPixelsRef pix = _pattern.getPixelsRef();

	vector<ofColor> colorSeed;
	colorSeed.resize(cDJSColorPatternNum);
	ofColor c(50, 200, 50);
	float angle = c.getHueAngle();
	angle += ofRandom(-180, 180);
	c.setHueAngle(angle);
	for (int i = 0; i < cDJSColorPatternNum; i++)
	{
		colorSeed[i] = c;
		angle += ofRandom(45, 90);
		c.setHueAngle(angle);
	}

	int diff = static_cast<int>((float)cDJSMaximunCheck / (cDJSColorPatternNum - 1));
	for (int i = 1; i < cDJSColorPatternNum; i++)
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

//-------------------------------------
void DJuliaSet::drawJuliaSetShader(ofPixelsRef pix, double real, double imaginary)
{
	_canvas.begin();
	ofClear(0);
	ofSetColor(255);
	_julia.begin();
	_julia.setUniformTexture("pattern", _pattern, 1);
	_julia.setUniform1f("real", real);
	_julia.setUniform1f("imaginary", imaginary);
	_julia.setUniform1f("width", cDJSCanvasWidth);
	_julia.setUniform1f("height", cDJSCanvasHeight);
	_julia.setUniform1f("rmin", cDJSRealPartRange.first);
	_julia.setUniform1f("rmax", cDJSRealPartRange.second);
	_julia.setUniform1f("imin", cDJSImaginePartRange.first);
	_julia.setUniform1f("imax", cDJSImaginePartRange.second);
	_julia.setUniform1i("iterMax", cDJSMaximunCheck);
	{
		_temp.draw(0, 0);
	}
	_julia.end();
	_canvas.end();

	_canvas.readToPixels(pix);
}


