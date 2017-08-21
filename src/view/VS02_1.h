#pragma once

#include "baseView.h"

class VS02_1 : public baseView
{
public:
	VS02_1(string path)
		:baseView(path)
	{}

	//-------------------------------
	void update(float delta) override
	{
	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		switch (_eState)
		{
		case eCenter:
		{
			drawCenter();
			break;
		}
		case eMiddleAndCenter:
		{
			drawMiddleAndCenter();
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
			_eState = eCenter;
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_eState = eMiddleAndCenter;
			squareMgr::GetInstance()->clearAllSquare();
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
		_das.setSize(_rect.width * 0.4);
		_das.setScale(_rect.width);
		_das.setColor(ofColor(255), ofColor(0));

		_das.start();
		
		camCtrl::GetInstance()->_squareCams[eSquareType::eBackCenerL].setRevolution(ofVec3f(-1, -1, 0), PI * 0.2);
		camCtrl::GetInstance()->_squareCams[eSquareType::eMiddleLeftM].setRevolution(ofVec3f(0, -1, 0), PI);
		camCtrl::GetInstance()->_squareCams[eSquareType::eMiddleRightM].setRevolution(ofVec3f(0, -1, 0), -PI);

		_eState = eCenter;
	}

	//-------------------------------
	void stop()
	{
		_das.stop();
	}

	//-------------------------------
	void setSoundValue(array<float, cBufferSize>& soundValue) override
	{
		_das.setSoundValue(soundValue);
	}

private:
	void drawCenter()
	{
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			_das.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);
	}

	void drawMiddleAndCenter()
	{
		
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			_das.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);
		
		_das.toggleFace();
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
		{
			_das.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleLeftM);

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleRightM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleRightM));
		{
			_das.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);
		_das.toggleFace();
	}
private:
	enum eState
	{
		eCenter = 0
		, eMiddleAndCenter

	}_eState;

	ofRectangle _rect;
	DAudioSphere	_das;
};