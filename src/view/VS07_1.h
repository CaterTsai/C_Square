#pragma once

#include "baseView.h"
#include "VideoMgr.h"

class VS07_1 : public baseView
{
public:
	VS07_1(string path)
		:baseView(path)
		, _addRipperTime(0.5)
		, _autoAddRipper(false)
	{}

	//-------------------------------
	void update(float delta) override
	{
		videoMgr::GetInstance()->update();

		_dpp.update(delta);
		if (_autoAddRipper)
		{
			_timer -= delta;
			if (_timer <= 0.0)
			{
				_dpp.triggerRipple();
				_timer = _addRipperTime;
			}
		}
	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		switch (_eState)
		{
		case eCenterPingPong:
		{
			drawCenterPingPong();
			break;
		}
		case eCenterAndSmallPingPong:
		{
			drawCenterAndSmallPingPong();
			break;
		}
		case eCenterRotateAndMiddlePingPong:
		{
			drawCenterRotateAndMiddlePingPong();
			break;
		}
		case eCenterAndSmallPingPongAndMiddleRotate:
		{
			drawCenterAndSmallPingPongAndMiddleRotate();
			break;
		}
		}
		ofPopStyle();
	};

	//-------------------------------
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "view 7-1\n";
		ss << "1 : Center Ping-Pong\n";
		ss << "2 : Center & Small Ping-Pong\n";
		ss << "3 : Center Video & Middle Ping-Pong\n";
		ss << "4 : Center & Small Ping-Pong And Middle Video\n";
		ss << "5 : Ping-Pong add Ball\n";
		ss << "6 : Ping-Pong add Ripple\n";
		ss << "7 : Ping-Pong clear Ball\n";

		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	//-------------------------------
	void control(eCtrlType type, int value) override
	{
		switch (type)
		{
		case eCtrl_ViewTrigger1:
		{
			if (value == cMidiButtonPress)
			{
				_eState = eCenterPingPong;
				squareMgr::GetInstance()->clearAllSquare();
			}
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			if (value == cMidiButtonPress)
			{
				_eState = eCenterAndSmallPingPong;
				squareMgr::GetInstance()->clearAllSquare();
			}
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			if (value == cMidiButtonPress)
			{
				_eState = eCenterRotateAndMiddlePingPong;
				squareMgr::GetInstance()->clearAllSquare();
			}
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			if (value == cMidiButtonPress)
			{
				_eState = eCenterAndSmallPingPongAndMiddleRotate;
				squareMgr::GetInstance()->clearAllSquare();
			}
			break;
		}
		case eCtrl_ViewTrigger5:
		{
			if (value == cMidiButtonPress)
			{
				_dpp.triggerBall();
			}
			break;
		}
		case eCtrl_ViewTrigger6:
		{
			if (value == cMidiButtonPress)
			{
				_dpp.triggerRipple();
			}
			break;
		}
		case eCtrl_ViewTrigger7:
		{
			if (value == cMidiButtonPress)
			{
				_dpp.clearBall();
			}
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		_eState = eCenterPingPong;
		_dpp.start();
		videoMgr::GetInstance()->play(eVideoRotate);

	}

	//-------------------------------
	void stop()
	{
		videoMgr::GetInstance()->stopAll();
		_dpp.stop();
	}

private:
	void drawCenterPingPong()
	{
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			_dpp.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);
	}

	void drawCenterAndSmallPingPong()
	{
		for (int i = 0; i < cSquareNum; i++)
		{
			if (i != eSquareType::eMiddleLeftM && i != eSquareType::eMiddleRightM)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					_dpp.draw(0, 0, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}
		}
	}

	void drawCenterRotateAndMiddlePingPong()
	{
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			videoMgr::GetInstance()->draw(eVideoRotate, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
		{
			ofPushMatrix();
			ofScale(-1, 1);
			_dpp.draw(0, 0, _rect.width, _rect.height);
			ofPopMatrix();
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleLeftM);

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleRightM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleRightM));
		{
			_dpp.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);
	}

	void drawCenterAndSmallPingPongAndMiddleRotate()
	{
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			_dpp.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
		{
			ofPushMatrix();
			ofScale(-1, 1);
			videoMgr::GetInstance()->draw(eVideoRotate, _rect.width, _rect.height);
			ofPopMatrix();
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleLeftM);

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleRightM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleRightM));
		{
			videoMgr::GetInstance()->draw(eVideoRotate, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);

		for (int i = 0; i < cSquareNum; i++)
		{
			if (i != eSquareType::eMiddleLeftM && i != eSquareType::eMiddleRightM)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					_dpp.draw(0, 0, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}
		}
	}
private:
	enum eState
	{
		eCenterPingPong = 0
		, eCenterAndSmallPingPong
		, eCenterRotateAndMiddlePingPong
		, eCenterAndSmallPingPongAndMiddleRotate
		
	}_eState;

	bool _autoAddRipper;
	float _timer, _addRipperTime;
	ofRectangle _rect;
	DPingPong	_dpp;
};