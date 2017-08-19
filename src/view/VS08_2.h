#pragma once

#include "baseView.h"

class VS08_2 : public baseView
{
public:
	VS08_2(string path)
		:baseView(path)
		, _triggerTime(0.5)
		, _autoTrigger(false)
	{}

	//-------------------------------
	void update(float delta) override
	{
		_dmr.update(delta);
		_dam.update(delta);

		if (_autoTrigger)
		{
			_timer -= delta;
			if (_timer <= 0.0)
			{
				_dmr.trigger();
				_timer = _triggerTime;
			}
		}
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
			_dmr.setGroupNum(cSquareNum);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_eState = eMoveRectAddAudioMesh;
			_dmr.setGroupNum(cSquareSmallNum);
			squareMgr::GetInstance()->clearAllSquare();
			_dmr.trigger();
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			_dmr.trigger();
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			_autoTrigger ^= true;
			_timer = 0.0;
			break;
		}
		case eCtrl_ViewTrigger5:
		{
			_dam.toggleBall();
			break;
		}
		case eCtrl_ViewTrigger6:
		{
			_dam.toggleLine();
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
	void drawMoveRect()
	{
		for (int i = 0; i < cSquareNum; i++)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(i);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
			{
				_dmr.draw(i, 0, 0, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(i);
		}
	}

	void drawMoveRectAddAudioMesh()
	{
		for (int i = 0; i < cSquareSmallNum; i++)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(i);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
			{
				_dmr.draw(i, 0, 0, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(i);
		}

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			_dam.draw(0, 0, _rect.width, _rect.height);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);
	}
private:
	enum eState
	{
		eMoveRect = 0
		, eMoveRectAddAudioMesh
	}_eState;
	ofRectangle _rect;
	DAudioMesh	_dam;
	DMoveRect	_dmr;

	bool _autoTrigger;
	float _timer, _triggerTime;
};