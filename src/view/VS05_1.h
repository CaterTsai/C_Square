#pragma once

#include "baseView.h"
#include "VideoMgr.h"
class VS05_1 : public baseView
{
public:
	VS05_1(string path)
		:baseView(path)
	{}

	//-------------------------------
	void update(float delta) override
	{
		videoMgr::GetInstance()->update();
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
			videoMgr::GetInstance()->stopAll();
			videoMgr::GetInstance()->play(eVideoMeiosis_1);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_eState = eMiddle;
			videoMgr::GetInstance()->stopAll();
			videoMgr::GetInstance()->play(eVideoMeiosis_2);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			_eState = eSmall;
			videoMgr::GetInstance()->stopAll();
			videoMgr::GetInstance()->play(eVideoMeiosis_3);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);

		videoMgr::GetInstance()->play(eVideoMeiosis_1);
		_eState = eCenter;
	}

	//-------------------------------
	void stop()
	{
		videoMgr::GetInstance()->stopAll();
	}

private:
	void drawCenter()
	{
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			videoMgr::GetInstance()->draw(eVideoMeiosis_1, _rect.width, _rect.height);
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
			videoMgr::GetInstance()->draw(eVideoMeiosis_2, _rect.width, _rect.height);
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
			videoMgr::GetInstance()->draw(eVideoMeiosis_2, _rect.width, _rect.height);
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
				videoMgr::GetInstance()->draw(eVideoMeiosis_3, _rect.width, _rect.height);
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
		, eMiddle
		, eSmall
	}_eState;

	ofRectangle _rect;

};