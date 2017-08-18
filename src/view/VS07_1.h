#pragma once

#include "baseView.h"

class VS07_1 : public baseView
{
public:
	VS07_1(string path)
		:baseView(path)
	{}

	//-------------------------------
	void update(float delta) override
	{
		_dpp.update(delta);
	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		switch (_eState)
		{
		case eOnlyCircle:
		{
			break;
		}
		case eCenterPingpong:
		{
			break;
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
			break;
		}
		case eCtrl_ViewTrigger2:
		{

			break;
		}
		case eCtrl_ViewTrigger3:
		{

			break;
		}
		case eCtrl_ViewTrigger4:
		{
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		_eState = eCenterPingpong;
		_dpp.start();

	}

	//-------------------------------
	void stop()
	{

	}

private:

private:
	enum eState
	{
		eOnlyCircle = 0
		, eCenterPingpong
	}_eState;

	ofRectangle _rect;
	DPingPong	_dpp;
};