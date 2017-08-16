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
	void control(eCtrlType type, int value) override
	{
		switch (type)
		{
		case eCtrl_ViewTrigger1:
		{
			_eca.trigger();
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_eState = eSingleCenter;
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			_eState = eDoubleMiddle;
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			_eState = eRandomSmall;
			setRandomSmall();
			squareMgr::GetInstance()->clearAllSquare();
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

		_eState = eSingleCenter;
	}
	
	//-------------------------------
	void stop()
	{

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
			_smallDisplay[i] = ((rand() % 2) == 1);
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