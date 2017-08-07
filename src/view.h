#pragma once

#include "constParameter.h"
#include "squareMgr.h"
#include "ofxXmlSettings.h"

class view
{
public:
	void load(string path)
	{

	}

	void set()
	{
		for (int i = 0; i < cSquareNum; i++)
		{
			squareMgr::GetInstance()->setSquareType(i, _squareType[i]);
			squareMgr::GetInstance()->setUnitRect(i, _squareCropRect[i]);
		}
	}

private:
	array<eSquareDrawType, cSquareNum> _squareType;
	array<ofRectangle, cSquareNum> _squareCropRect;
};
