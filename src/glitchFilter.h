#pragma once

#include "constParameter.h"
#include "ofxPostGlitch.h"

enum eGlitchType
{
	eGlitchLittle = 0
	,eGlitchNoice
	,eGlitchTwist
	,eGlitchSwell
	,eGlitchShake
};

class glitchFilter
{
public:
	void set(int width, int height);
	void draw(int x, int y, int w, int h);
	
	void begin();
	void end();

	void setGlitchType(eGlitchType type);

private:
	
	ofFbo _raw;
	ofxPostGlitch	_glitch;
};