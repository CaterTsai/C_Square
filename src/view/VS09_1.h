#pragma once

#include "baseView.h"

class VS09_1 : public baseView
{
public:
	VS09_1(string path)
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
		case eMiddle:
		{
			drawMiddle();
			break;
		}
		case eSmall:
		{
			drawSmall();
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
			_eState = eMiddle;
			_dar.setHorizon(false);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			_eState = eSmall;
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			_dar.toggleHorizon();
			break;
		}
		case eCtrl_ViewTrigger5:
		{
			break;
		}
		case eCtrl_ViewTrigger6:
		{
			break;
		}
		}
	}

	//-------------------------------
	void setSoundValue(array<float, cBufferSize>& soundValue) override
	{
		_dar.setSoundValue(soundValue);
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		_dar.start();
		_eState = eCenter;
	}

	//-------------------------------
	void stop()
	{
		_dar.stop();
	}

private:
	void drawCenter()
	{
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			_dar.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);
	}

	void drawMiddle()
	{
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
		{
			_dar.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleLeftM);

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleRightM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleRightM));
		{
			ofPushMatrix();
			ofScale(-1, 1);
			_dar.draw(0, 0, _rect.width, _rect.height);
			ofPopMatrix();
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);
	}

	void drawSmall()
	{
		for (int i = 0; i < cSquareSmallNum; i++)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(i);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
			{
				_dar.draw(0, 0, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(i);
		}
	}
private:
	enum eState
	{
		eCenter = 0
		,eMiddle
		,eSmall
	}_eState;

	DAudioRect _dar;
	ofRectangle _rect;

	
};