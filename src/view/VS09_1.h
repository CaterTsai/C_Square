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
		case eMoveRect:
		{
			drawMoveRect();
			break;
		}
		case eMoveRectAddAudioMesh:
		{
			drawMoveRectAddAudioMesh();
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
			_eState = eMoveRect;
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_eState = eMoveRectAddAudioMesh;
			squareMgr::GetInstance()->clearAllSquare();
			_dmr.trigger();
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
		_dam.setSoundValue(soundValue);
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		_dmr.setGroupNum(7);
		_dmr.start();
		_dam.start();
		_eState = eMoveRect;


		camCtrl::GetInstance()->_squareCams[eSquareType::eBackCenerL].setFixed(ofVec3f(0, -50, 55));

	}

	//-------------------------------
	void stop()
	{

	}

private:
	
private:
	enum eState
	{
		eMoveRect = 0
		, eMoveRectAddAudioMesh
	}_eState;

	ofRectangle _rect;

	
};