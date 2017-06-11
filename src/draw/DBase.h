#pragma once

#include "../constParameter.h"
#include "DType.h"

#define CHECK_START() if(!isStart)return;

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
		:eType(type)
		, isStart(false)
	{};

	virtual void update(float delta) {};
	virtual void draw() {};
	virtual void draw(int x, int y, int z = 0) {};
	virtual void draw(int x, int y, int w, int h) {};

	virtual void start() {};
	virtual void stop() {};
	
	virtual void reset() {};

	virtual void setValue(DParam& value) {};
	virtual void setValue(DParam& value, DParam& value2) {};
	virtual void setValue(DParam& value, DParam& value2, DParam& value3) {};

	virtual void setColor(ofColor& color) {};
	virtual void setColor(ofColor& color, ofColor& color2) {};
	virtual void setColor(ofColor& color, ofColor& color2, ofColor& color3) {};
	
	virtual void onBeat() {};


	inline bool getStart()
	{
		return isStart;
	}

	inline eDType getType()
	{
		return eType;
	};

protected:
	bool isStart;
	const eDType	eType;

};