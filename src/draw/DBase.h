#pragma once

#include "constParameter.h"
#include "squareMgr.h"
#include "DType.h"

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
		, isSetup(false)
		, isStart(false)
	{};

	virtual void setup() {};
	virtual void update(float delta) {};
	virtual void draw() {};
	virtual void start() {};
	virtual void reset() {};

	virtual void setValue(DParam& value) {};
	virtual void setValue(DParam& value, DParam& value2) {};
	virtual void setValue(DParam& value, DParam& value2, DParam& value3) {};

	virtual void setColor(ofColor& color) {};
	virtual void setColor(ofColor& color, ofColor& color2) {};
	virtual void setColor(ofColor& color, ofColor& color2, ofColor& color3) {};
	
	virtual void onBeat() {};

	inline bool getSetup()
	{
		return isSetup;
	}

	inline bool getStart()
	{
		return isStart;
	}

	inline eDType getType()
	{
		return eType;
	};

protected:
	bool isSetup, isStart;
	const eDType	eType;

};