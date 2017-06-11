#pragma once

#include "constParameter.h"
#include "squareMgr.h"
#include "drawer.h"
#include "SType.h"

class SBase
{

public:
	SBase(eSType type)
		:_isStart(false)
		,_eType(type)
	{}

	virtual void update(float delta) {};
	virtual void draw() {};
	virtual void start() {};
	virtual void stop() {};
	virtual void reset() {};

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
};