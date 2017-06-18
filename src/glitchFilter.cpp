#include "glitchFilter.h"

//--------------------------------------------------------------
void glitchFilter::set(int width, int height)
{

	_raw.allocate(width, height);
	_glitch.setFbo(&_raw);
}

//--------------------------------------------------------------
void glitchFilter::draw(int x, int y, int w, int h)
{
	ofPushStyle();
	ofSetColor(255);
	_raw.draw(x, y, w, h);
	ofPopStyle();
}

//--------------------------------------------------------------
void glitchFilter::begin()
{
	_raw.begin();
	ofClear(0);
}

//--------------------------------------------------------------
void glitchFilter::end()
{
	_raw.end();
	_glitch.generateFx();
}

//--------------------------------------------------------------
void glitchFilter::setGlitchType(eGlitchType type)
{
	//Disable All
	for (int i = 0; i < GLITCH_NUM; i++)
	{
		_glitch.setFx((ofxPostGlitchType)i, false);
	}

	switch (type)
	{
		case eGlitchLittle:
		{
			_glitch.setFx(OFXPOSTGLITCH_GLOW, true);
			_glitch.setFx(OFXPOSTGLITCH_SWELL, true);

		}
	}
}