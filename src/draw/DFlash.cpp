#include "DFlash.h"


//-------------------------------------
void DFlash::update(float delta)
{
	CHECK_START();

	if (_autoFlash)
	{
		_timer -= delta;
		if (_timer <= 0.0f)
		{
			_timer = _flashT;
			_flash = true;
		}
	}
	
}

//-------------------------------------
void DFlash::draw(int x, int y, int w, int h)
{
	CHECK_START();
	if (_flash)
	{
		ofPushStyle();
		ofFill();
		ofSetColor(_flashColor);
		{
			ofDrawRectangle(w * -0.5, h * -0.5, w, h);
		}
		ofPopStyle();
		_flash = false;
	}
}

//-------------------------------------
void DFlash::start()
{
	_isStart = true;
}

//-------------------------------------
void DFlash::stop()
{
	_isStart = false;
}

//-------------------------------------
void DFlash::trigger()
{
	_flash = true;
}

//-------------------------------------
void DFlash::setAutoFlash(bool val, float time)
{
	_autoFlash = val;
	_flashT = time;
}
