#pragma once

#include "constParameter.h"
#include "squareMgr.h"
#include "ofxXmlSettings.h"
#include "ctrlMap.h"
#include "drawer.h"
#include "camCtrl.h"
#include "postFilter.h"
#include "midiCtrl.h"
class baseView
{
public:
	baseView(string path)
	{
		load(path);
	}
	virtual void update(float delta) {};
	virtual void draw(int width, int height) {};
	virtual void drawCanvas(int x, int y, int width, int height) {};
	virtual void drawMsg(ofVec2f pos) {}; //Debug
	virtual void control(eCtrlType type, int value) {};
	virtual void start() {};
	virtual void stop() {};
	virtual void setSoundValue(array<float, cBufferSize>& soundValue) {};
	//View Setting
	void load(string path)
	{
		ofxXmlSettings xml;
		if (!xml.load(path))
		{
			ofLog(OF_LOG_ERROR, "[view::load]load faield :" + path);
			return;
		}

		for (int i = 0; i < cSquareNum; i++)
		{
			xml.pushTag("square", i);
			{
				_squareType[i] = (eSquareDrawType)xml.getValue("squareType", 0, 0);
				xml.pushTag("cropRect", 0);
				{
					_squareCropRect[i].setX(xml.getValue("x", 0, 0));
					_squareCropRect[i].setY(xml.getValue("y", 0, 0));
					_squareCropRect[i].setWidth(xml.getValue("width", 0, 0));
					_squareCropRect[i].setHeight(xml.getValue("height", 0, 0));
				}
				xml.popTag();
			}
			xml.popTag();
		}
	}
	void set()
	{
		for (int i = 0; i < cSquareNum; i++)
		{
			squareMgr::GetInstance()->setSquareType(i, _squareType[i]);
			squareMgr::GetInstance()->setUnitRect(i, _squareCropRect[i]);
		}
	}

protected:
	array<eSquareDrawType, cSquareNum> _squareType;
	array<ofRectangle, cSquareNum> _squareCropRect;
};
