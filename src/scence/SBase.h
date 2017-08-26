#pragma once

#include "constParameter.h"
#include "squareMgr.h"
#include "drawer.h"
#include "SType.h"
#include "ctrlMap.h"
#include "camCtrl.h"
#include "postFilter.h"
#include "baseView.h"

class SBase
{

public:
	SBase(eSType type)
		:_isStart(false)
		,_eType(type)
		, _viewID(0)
	{
	}

	virtual void update(float delta) {
		if (!_isStart || _viewList.size() == 0)
		{
			return;
		}

		//for (auto& iter : _viewList)
		//{
		//	iter->update(delta);
		//}
		_viewList[_viewID]->update(delta);
	};
	virtual void draw() {
		if (!_isStart || _viewList.size() == 0)
		{
			return;
		}

		_viewList[_viewID]->draw(0, 0);
	};
	virtual void drawCanvas(int x, int y, int width, int height) {
		_viewList[_viewID]->drawCanvas(x, y, width, height);
	}
	virtual void drawViewMsg(ofVec2f pos)
	{
		ofDrawBitmapStringHighlight("View Num : " + ofToString(_viewList.size()), pos);
		if (_viewList.size() > _viewID)
		{
			_viewList[_viewID]->drawMsg(pos + ofVec2f(0, 15));
		}
		
	}
	virtual void start() {
		_isStart = true;
		_viewID = 0;
		if (_viewList.size() > _viewID)
		{
			_viewList[_viewID]->set();
			_viewList[_viewID]->start();
		}
	};
	virtual void stop() {
		_isStart = false;
	};
	virtual void reset() {};
	virtual void control(eCtrlType ctrl, int value = cMidiButtonPress) {
		if (ctrl == eCtrl_ViewNext)
		{
			if (value == cMidiButtonPress)
			{
				setView((_viewID + 1) % _viewList.size());
				_viewList[_viewID]->start();
				squareMgr::GetInstance()->clearAllSquare();
				squareMgr::GetInstance()->clearGroup();

				
			}
		}
		else
		{
			if (ctrl > eCtrl_View && ctrl < eCtrl_ViewNum)
			{
				_viewList[_viewID]->control(ctrl, value);
			}
		}
	};
	virtual void setSoundValue(array<float, cBufferSize>& soundValue) 
	{
		if (_viewList.size() > _viewID)
		{
			_viewList[_viewID]->setSoundValue(soundValue);
		}
	};
	virtual inline string getScenceName() { return "SBase"; };
	//View
	virtual void initView() {};
	virtual void setView(int id) {};

	inline bool getStart()
	{
		return _isStart;
	}

	inline eSType getType()
	{
		return _eType;
	};

public:
	bool _isStart;
	eSType _eType;

	int _viewID;
	vector<ofPtr<baseView>> _viewList;
};