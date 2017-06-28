#pragma once

#include "../constParameter.h"
#include "DType.h"

#define CHECK_START() if(!_isStart)return;

union DParam
{
	int iValue;
	float fValue;
	string* sValue;
};

class DBase
{
public:
	DBase(eDType type)
		:_eType(type)
		,_isStart(false)
		, _timer(0.0f)
	{};

	virtual void update(float delta) {};
	virtual void draw() {};
	virtual void draw(int x, int y, int z = 0) {};
	virtual void draw(int x, int y, int w, int h) {};

	virtual void start() {};
	virtual void stop() {};
	
	virtual void reset() {};

	virtual void trigger() {};
	virtual void setValue(DParam& value) {};
	virtual void setValue(DParam& value, DParam& value2) {};
	virtual void setValue(DParam& value, DParam& value2, DParam& value3) {};

	virtual void setColor(ofColor& color) {};
	virtual void setColor(ofColor& color, ofColor& color2) {};
	virtual void setColor(ofColor& color, ofColor& color2, ofColor& color3) {};
	
	virtual void onBeat() {};


	inline bool getStart()
	{
		return _isStart;
	}

	inline eDType getType()
	{
		return _eType;
	};

protected:
	bool _isStart;
	const eDType	_eType;
	float _timer;

};