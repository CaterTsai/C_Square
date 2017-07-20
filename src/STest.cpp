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
	_djs.update(delta);
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
		_post.begin(_cam);
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
			_djs.draw(0, 0, _drawRect.width, _drawRect.height);
		}	
		_post.end();
		ofDisableDepthTest();

		
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
	//_dp.setBaseSize(_drawRect.width * 0.5);
	//_dp.start();
	
	//_cf.start();
	//_dr.start();
	//_ds.start();
	//_dm.setBaseSize(_drawRect.width);
	//_dm.start();
	//_dpp.start();
	//_dms.start();
	_djs.start();

	setupPost();

	//_cam.setDistance(1800);
	//_cam.setTarget(ofVec3f(0, 0, 0));

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
void STest::trigger()
{
	//_dp.trigger();
	//_dr.trigger();
	//_dm.trigger();
}

//-------------------------------------
void STest::setupPost()
{
	if (_post.getNumProcessedPasses() == 0)
	{
		_post.init(_drawRect.getWidth(), _drawRect.getHeight());

		//_post.createPass<FxaaPass>()->setEnabled(true);
		//_post.createPass<BloomPass>()->setEnabled(true);
		//_post.createPass<BloomPass>()->setEnabled(true);
		//_post.createPass<NoiseWarpPass>()->setEnabled(true);
		//_post.createPass<ZoomBlurPass>()->setEnabled(true);
		//_post.createPass<LimbDarkeningPass>()->setEnabled(true);
	}

}
