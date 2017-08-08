#include "STest.h"

STest::STest()
	:SBase(eSTest)
{
	initView();
	_img.loadImage("giraffe.jpg");
}

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
	//_dmr.update(delta);

}

//-------------------------------------
void STest::draw()
{
	if (!_isStart)
	{
		return;
	}

	switch (_viewID)
	{
		case 0:
		{
			view1Draw();
			break;
		}
		case 1:
		{
			view2Draw();
			break;
		}
	}
}

//-------------------------------------
void STest::start()
{
	_drawRect = squareMgr::GetInstance()->getUnitRect(0);

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
	//_dmr.setGroupNum(2);
	//_dmr.start();
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
	if (ctrl == eCtrl_ViewNext)
	{
		setView( (_viewID + 1) % _viewList.size());
	}
	else
	{

	}
}

#pragma region View
//-------------------------------------
void STest::initView()
{
	_viewList.resize(2);
	_viewList[0].load("view/sTest/1.xml");
	_viewList[1].load("view/sTest/2.xml");
}

//-------------------------------------
void STest::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[STest::setView]id out of range");
		return;
	}

	_viewList[id].set();
	_viewID = id;
}

//-------------------------------------
void STest::view1Draw()
{
	ofColor color(255, 0, 0);

	ofPushStyle();
	{
		for (int i = 0; i < cSquareNum; i++)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(i);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
			{
				color.setHueAngle(i * 30);
				ofSetColor(color);
				ofDrawBox(100);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(i);
		}
	}
	ofPopStyle();
}

//-------------------------------------
void STest::view2Draw()
{
	ofPushStyle();
	ofEnableDepthTest();
	{
		squareMgr::GetInstance()->updateByGroup(_img);
	}
	ofPopStyle();
}
#pragma endregion



