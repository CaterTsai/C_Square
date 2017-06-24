#include "STest.h"

//-------------------------------------
void STest::update(float delta)
{
	if (!_isStart)
	{
		return;
	}
	_cl.update(delta);
	//_life.update(delta);
	//_eca.update(delta);

	//_enableGlitch = (ofGetFrameNum() % 5 == 0 && rand() % 10 < 5 ) ? true : false;

	//if (_enableGlitch)
	//{
	//	_glitch.begin();
	//	{
	//		_life.draw(0, 0, _drawRect.width, _drawRect.height);
	//	}
	//	_glitch.end();
	//}
	
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
		squareMgr::GetInstance()->updateOnUnitBegin(0, false);
		
		//ofFill();
		//ofSetColor(255, 1);
		//ofDrawRectangle(_drawRect);
		//if (_enableGlitch)
		//{
		//	_glitch.draw(0, 0, _drawRect.width, _drawRect.height);
		//}
		//else
		//{
		//	_life.draw(0, 0, _drawRect.width, _drawRect.height);
		//}
		
		//_eca.draw(0, 0, _drawRect.width, _drawRect.height);
		_cl.draw(0, 0, _drawRect.width, _drawRect.height);
		
		squareMgr::GetInstance()->updateOnUnitEnd(0);
	}
	ofPopStyle();
}

//-------------------------------------
void STest::start()
{
	_drawRect = squareMgr::GetInstance()->getUnitRect(0);
	squareMgr::GetInstance()->updateOnUnitBegin(0);
	ofClear(255, 0);
	squareMgr::GetInstance()->updateOnUnitEnd(0);
	_isStart = true;
	//_life.start();
	//_eca.start();
	_cl.start();
	_glitch.set(_drawRect.width, _drawRect.height);
	_glitch.setGlitchType(eGlitchType::eGlitchCut);

}

//-------------------------------------
void STest::stop()
{
	_isStart = false;
	_cl.stop();
	//_life.stop();
	//_eca.stop();
	
}
