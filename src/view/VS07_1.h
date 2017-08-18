#pragma once

#include "baseView.h"

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
		}
		}
		ofPopStyle();
	};

	//-------------------------------
	void control(eCtrlType type, int value) override
	{
		switch (type)
		{
		case eCtrl_ViewTrigger1:
		{
			_eState = eCenterPingPong;
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_eState = eCenterAndSmallPingPong;
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			_dpp.triggerBall();
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			_dpp.triggerRipple();
			break;
		}
		case eCtrl_ViewTrigger5:
		{
			_dpp.clearBall();
			break;
		}
		case eCtrl_ViewTrigger6:
		{
			_autoAddRipper ^= true;
			_timer = 0.0;
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

	}

	//-------------------------------
	void stop()
	{

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
private:
	enum eState
	{
		eCenterPingPong = 0
		, eCenterAndSmallPingPong
	}_eState;

	bool _autoAddRipper;
	float _timer, _addRipperTime;
	ofRectangle _rect;
	DPingPong	_dpp;
};