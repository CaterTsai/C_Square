#pragma once

#include "baseView.h"

class VSIdle : public baseView
{
public:
	VSIdle(string path)
		:baseView(path)
	{
		_font.load("font/font.ttf", 50);

	}

	//-------------------------------
	void update(float delta) override
	{

	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		int value = _targetTime - getNowTimeValue();
		string time = (value > 0) ? ofToString(value) : "0";
		auto rect = _font.getStringBoundingBox(time, 0, 0);
		ofSetColor(255);
		for (int i = 0; i < cSquareNum; i++)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(i);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
			{
				
				_font.drawString(time, rect.width * -0.5, rect.height * 0.5);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(i);
		}
		ofPopStyle();
	}

	//-------------------------------
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "view Idle\n";

		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	//-------------------------------
	void control(eCtrlType type, int value) override
	{
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		_targetTime = getTimeValue(30, 0, 0);

		for (int i = 0; i < cSquareNum - 1; i++)
		{
			float v = PI * ofRandom(0.1, 0.3);
			v *= (rand() % 2 == 0 ? -1 : 1);
			camCtrl::GetInstance()->_squareCams[i].setRevolution(ofVec3f(0, -1, 0), v);
		}
		
	}

	//-------------------------------
	void stop()
	{
		
	}

private:
	int getNowTimeValue()
	{
		int m = stoi(ofGetTimestampString("%M"));
		int s = stoi(ofGetTimestampString("%S"));
		int i = stoi(ofGetTimestampString("%i"));
		return getTimeValue(m, s, i);
	}
	int getTimeValue(int m, int s, int i)
	{
		return m * 6000 + s * 1000 + i;
	}
private:
	int _targetTime;
	ofTrueTypeFont _font;
	ofRectangle _rect;
};