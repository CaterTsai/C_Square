#include "DFlash.h"


//-------------------------------------
void DFlash::update(float delta)
{
	CHECK_START();

	_timer -= delta;
	if (_timer <= 0.0f)
	{
		_timer = _flashT;
		_flash = true;
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
			ofDrawRectangle(x, y, w, h);
		}
		ofPopStyle();
		_flash = false;
	}
}

//-------------------------------------
void DFlash::start()
{
	_timer = _flashT;
	_isStart = true;
}

//-------------------------------------
void DFlash::stop()
{
	_isStart = false;
}

//-------------------------------------
void DFlash::setValue(DParam & value)
{
	_flashT = value.fValue;
}
