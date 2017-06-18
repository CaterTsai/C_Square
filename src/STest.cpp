#include "STest.h"

//-------------------------------------
void STest::update(float delta)
{
	if (!_isStart)
	{
		return;
	}
	_life.update(delta);
	//_eca.update(delta);

	_glitch.begin();
	{
		_life.draw(0, 0, _drawRect.width, _drawRect.height);
	}
	_glitch.end();
}

//-------------------------------------
void STest::draw()
{
	if (!_isStart)
	{
		return;
	}

	ofPushStyle();
	{
		squareMgr::GetInstance()->updateOnUnitBegin(0);
		//_life.draw(0, 0, _drawRect.width, _drawRect.height);
		//_eca.draw(0, 0, _drawRect.width, _drawRect.height);
		_glitch.draw(0, 0, _drawRect.width, _drawRect.height);
		
		squareMgr::GetInstance()->updateOnUnitEnd(0);
	}
	ofPopStyle();
}

//-------------------------------------
void STest::start()
{
	_drawRect = squareMgr::GetInstance()->getUnitRect(0);
	_isStart = true;
	_life.start();
	//_eca.start();
	_glitch.set(_drawRect.width, _drawRect.height);
	_glitch.setGlitchType(eGlitchType::eGlitchLittle);

}

//-------------------------------------
void STest::stop()
{
	_isStart = false;
	_life.stop();
	//_eca.stop();
	
}
