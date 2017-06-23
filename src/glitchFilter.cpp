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
		case eGlitchNormal:
		{
			_glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
			_glitch.setFx(OFXPOSTGLITCH_SHAKER, true);
			_glitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE, true);
			break;
		}
		case eGlitchNoise:
		{
			_glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
			_glitch.setFx(OFXPOSTGLITCH_NOISE, true);
			_glitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE, true);
			break;
		}
		case eGlitchHeavy:
		{
			_glitch.setFx(OFXPOSTGLITCH_TWIST, true);
			_glitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
			break;
		}
		case eGlitchSwell:
		{
			_glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
			_glitch.setFx(OFXPOSTGLITCH_SWELL, true);
			_glitch.setFx(OFXPOSTGLITCH_INVERT, true);
			break;
		}
		case eGlitchCut:
		{
			_glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
			_glitch.setFx(OFXPOSTGLITCH_CUTSLIDER, true);
			_glitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE, true);
			_glitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE, true);
			break;
		}
		case eGlitchSlitscan:
		{
			_glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
			_glitch.setFx(OFXPOSTGLITCH_SLITSCAN, true);
			break;
		}

	}
}