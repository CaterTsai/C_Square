#pragma once

#include "baseView.h"

class VS04_1 : public baseView
{
public:
	VS04_1(string path)
		:baseView(path)
	{}

	//-------------------------------
	void update(float delta) override
	{
		_eca.update(delta);
	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		switch (_eState)
		{
			case eSingleCenter:
			{
				drawSingleCenter();
				break;
			}
			case eDoubleMiddle:
			{
				drawDoubleMiddle();
				break;
			}
			case eRandomSmall:
			{
				drawRandomSmall();
				break;
			}
		}
		ofPopStyle();
	};

	//-------------------------------
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "view 4-1\n";
		ss << "1 : Center\n";
		ss << "2 : Middle\n";
		ss << "3 : Small\n";
		ss << "4 : ECA Trigger\n";
		ss << "5 : (L)Flash\n";

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
				_eState = eSingleCenter;
				squareMgr::GetInstance()->clearAllSquare();
			}
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			if (value == cMidiButtonPress)
			{
				_eState = eDoubleMiddle;
				squareMgr::GetInstance()->clearAllSquare();
			}
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			if (value == cMidiButtonPress)
			{
				_eState = eRandomSmall;
				setRandomSmall();
				squareMgr::GetInstance()->clearAllSquare();
			}
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			if (value == cMidiButtonPress)
			{
				_eca.trigger();
			}
			break;
		}
		case eCtrl_ViewTrigger5:
		{
			if (value == cMidiButtonPress)
			{
				LFlash flash;
				flash.time = static_cast<int>(60.0 / globalVariable::gBPM * 1000);
				flash.enable1 = true;
				flash.enable2 = true;
				flash.enable3 = true;
				flash.enable4 = true;
				sender::GetInstance()->sendAll(flash);
			}
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		_eca.setT(0.2);
		_eca.start();

		camCtrl::GetInstance()->_squareCams[eSquareType::eMiddleLeftM].setRevolution(ofVec3f(0, -1, 0), PI * 0.2);
		camCtrl::GetInstance()->_squareCams[eSquareType::eMiddleRightM].setRevolution(ofVec3f(0, -1, 0), PI * -0.2);
		camCtrl::GetInstance()->reset();
		_eState = eSingleCenter;
	}
	
	//-------------------------------
	void stop()
	{
		_eca.stop();
	}

private:
	//-------------------------------
	void drawSingleCenter() {
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			_eca.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);
	}

	//-------------------------------
	void drawDoubleMiddle()
	{
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
		{
			_eca.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleLeftM);

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleRightM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleRightM));
		{
			_eca.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);
	}

	//-------------------------------
	void drawRandomSmall()
	{
		for (int i = 0; i < cSquareSmallNum; i++)
		{
			if (_smallDisplay[i])
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					_eca.draw(0, 0, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}
		}
	}

	//-------------------------------
	void setRandomSmall()
	{
		ZeroMemory(_smallDisplay, sizeof(bool) * cSquareSmallNum);
		
		for (int i = 0; i < cSquareSmallNum; i++)
		{
			_smallDisplay[i] = true;
		}
	}
private:
	enum eState
	{
		eSingleCenter	=	0
		,eDoubleMiddle
		,eRandomSmall
	}_eState;

	bool _smallDisplay[cSquareSmallNum];
	ofRectangle _rect;
	DECA	_eca;
};