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
	//_dp.update(delta);
	//_cf.update(delta);
	//_dr.update(delta);
	//_ds.update(delta);
	//_dm.update(delta);
	//_dpp.update(delta);
	//_dms.update(delta);
	//_djs.update(delta);
	//_dtp.update(delta);
	//_dam.update(delta);
	_dmr.update(delta);

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
		ofEnableDepthTest();		
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(0));
		{
			//_life.draw(0, 0, _drawRect.width, _drawRect.height);
			//_dp.draw(0, 0, _drawRect.width, _drawRect.height);
			//_cf.draw(0, 0, _drawRect.width, _drawRect.height * 0.2);
			//_eca.draw(0, 0, _drawRect.width * 2, _drawRect.height * 2);
			//_dr.draw(0, 0, _drawRect.width, _drawRect.height);
			//_ds.draw(0, 0, _drawRect.width, _drawRect.height);
			//_dm.draw(0, 0, _drawRect.width, _drawRect.height);
			//_dpp.draw(0, 0, _drawRect.width, _drawRect.height);
			//_dms.draw(0, 0, _drawRect.width, _drawRect.height);
			//_djs.draw(0, 0, _drawRect.width, _drawRect.height);
			//_dam.draw(0, 0, _drawRect.width, _drawRect.height);
			_dmr.draw(0, 0, 0, _drawRect.width, _drawRect.height);

			//Texture
			//_img.getTexture().bind();
			//_dtp.draw(0, 0, _drawRect.width, _drawRect.height);
			//_img.getTexture().unbind();
		}	
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();

		//_eca.draw(0, 0, _drawRect.width, _drawRect.height);
		//_cl.draw(0, 0, _drawRect.width, _drawRect.height);
		
		squareMgr::GetInstance()->updateOnUnitEnd(0);

		squareMgr::GetInstance()->updateOnUnitBegin(1);
		ofEnableDepthTest();
		
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(1));
		{
			_dmr.draw(1, 0, 0, _drawRect.width, _drawRect.height);
			
		}
		postFilter::GetInstance()->_squarePost.end();
		
		squareMgr::GetInstance()->updateOnUnitEnd(1);
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
	
	squareMgr::GetInstance()->updateOnUnitBegin(1);
	ofClear(0);
	squareMgr::GetInstance()->updateOnUnitEnd(1);

	_isStart = true;
	//_life.start();
	//_eca.start();
	//_cl.start();
	//_dp.setBaseSize(_drawRect.width * 0.5);
	//_dp.start();
	
	//_cf.start();
	//_dr.start();
	//_ds.start();
	//_dm.setBaseSize(_drawRect.width);
	//_dm.start();
	//_dpp.start();
	//_dms.start();
	//_djs.start();
	
	//_dtp.setBaseSize(_drawRect.width * 0.5);
	//_dtp.setTextrue(_img.getTexture());
	//_dtp.start();

	//_dam.start();
	_dmr.setGroupNum(2);
	_dmr.start();
	//camCtrl::GetInstance()->_squareCams[0].setRevolution(ofVec3f(0, -1, 0), PI);
	//camCtrl::GetInstance()->_squareCams[1].setRevolution(ofVec3f(0, -1, 0), -PI);
}

//-------------------------------------
void STest::stop()
{
	_isStart = false;
	
	//_life.stop();
	//_eca.stop();
	//_cl.stop();
	//_dp.stop();
	//_cf.stop();
}

//-------------------------------------
void STest::control(eCtrlType ctrl, int value)
{
	//_dp.trigger();
	//_dr.trigger();
	//_dm.trigger();
	//_dtp.trigger();
	_dmr.trigger();
}

