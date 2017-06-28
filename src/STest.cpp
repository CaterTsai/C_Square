#include "STest.h"

//-------------------------------------
void STest::update(float delta)
{
	if (!_isStart)
	{
		return;
	}
	
	//_life.update(delta);
	//_eca.update(delta);
	//_cl.update(delta);

	
	_dp.update(delta);
	//_cf.update(delta);

	//_enableGlitch = (ofGetFrameNum() % 5 == 0 && rand() % 10 < 5 ) ? true : false;

	//if (_enableGlitch)
	//{
	//	_glitch.begin();
	//	{
	//		_life.draw(0, 0, _drawRect.width, _drawRect.height);
	//	}
	//	_glitch.end();
	//}
	if (_autoRotate)
	{
		_cam.rotateAround(delta * 30, ofVec3f(0, -1, 0), ofVec3f(0, 0, 0));
		_cam.lookAt(ofVec3f(0, 0, 0));
	}
		
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
		squareMgr::GetInstance()->updateOnUnitBegin(0, true);

		ofEnableDepthTest();
		_cam.begin();
		{
			_dp.draw(0, 0, _drawRect.width, _drawRect.height);
			//_cf.draw(0, 0, _drawRect.width, _drawRect.height * 0.5);
		}	
		_cam.end();
		ofDisableDepthTest();

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
		//_cl.draw(0, 0, _drawRect.width, _drawRect.height);
		
		
		squareMgr::GetInstance()->updateOnUnitEnd(0);
	}
	
	ofPopStyle();
}

//-------------------------------------
void STest::start()
{
	_drawRect = squareMgr::GetInstance()->getUnitRect(0);
	squareMgr::GetInstance()->updateOnUnitBegin(0);
	ofClear(0);
	squareMgr::GetInstance()->updateOnUnitEnd(0);
	
	_isStart = true;
	//_life.start();
	//_eca.start();
	//_cl.start();
	_dp.start();
	_dp.setBaseSize(_drawRect.width * 0.5);

	//_cf.start();
	_glitch.set(_drawRect.width, _drawRect.height);
	_glitch.setGlitchType(eGlitchType::eGlitchCut);

	_cam.setDistance(1800);
	_cam.setTarget(ofVec3f(0, 0, 0));

}

//-------------------------------------
void STest::stop()
{
	_isStart = false;
	
	//_life.stop();
	//_eca.stop();
	//_cl.stop();
	//_dp.stop();
	_cf.stop();
}

//-------------------------------------
void STest::trigger()
{
	_dp.trigger();
}
