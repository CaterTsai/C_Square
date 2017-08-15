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
		switch (_eState)
		{
		case eSingleCenter:
		{
			ofPushStyle();
			{
				drawSingleCenter();
			}
			ofPopStyle();
			break;
		}
		case eDoubleMiddle:
		{
			ofPushStyle();
			{
				drawDoubleMiddle();
			}
			ofPopStyle();
		}
		}

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
			squareMgr::GetInstance()->clearSquare(eSquareType::eMiddleLeftM);
			squareMgr::GetInstance()->clearSquare(eSquareType::eMiddleRightM);
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			_eState = eDoubleMiddle;
			squareMgr::GetInstance()->clearSquare(eSquareType::eBackCenerL);
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

		camCtrl::GetInstance()->_squareCams[eSquareType::eMiddleLeftM].setPlayType(eCamMovePlayType::eMoveRepeatBack);
		camCtrl::GetInstance()->_squareCams[eSquareType::eMiddleLeftM].setRevolution(ofVec3f(0, -1, 0), PI * -0.5, PI * 0.5, 10.0);
		camCtrl::GetInstance()->_squareCams[eSquareType::eMiddleRightM].setPlayType(eCamMovePlayType::eMoveRepeatBack);
		camCtrl::GetInstance()->_squareCams[eSquareType::eMiddleRightM].setRevolution(ofVec3f(0, -1, 0), PI * 0.5, PI * -0.5, 10.0);

		_eState = eSingleCenter;
	}
	
	//-------------------------------
	void stop()
	{

	}

private:
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

private:
	enum eState
	{
		eSingleCenter	=	0
		,eDoubleMiddle
	}_eState;
	ofRectangle _rect;
	DECA	_eca, _eca2;
};