#pragma once

#include "constParameter.h"
#include "squareMgr.h"
#include "drawer.h"
#include "SType.h"
#include "ctrlMap.h"
#include "view.h"

class SBase
{

public:
	SBase(eSType type)
		:_isStart(false)
		,_eType(type)
		, _viewID(0)
	{
	}

	virtual void update(float delta) {};
	virtual void draw() {};
	virtual void start() {};
	virtual void stop() {};
	virtual void reset() {};
	virtual void control(eCtrlType ctrl, int value = 0) {};

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
	vector<view> _viewList;
};