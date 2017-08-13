#pragma once

#include "baseView.h"

class VSTest01 : public baseView
{
public:
	VSTest01(string path)
		:baseView(path)
	{}

	void draw(int width, int height) override
	{
		ofColor color(255, 0, 0);

		ofPushStyle();
		{
			for (int i = 0; i < cSquareNum; i++)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					color.setHueAngle(i * 30);
					ofSetColor(color);
					ofDrawBox(100);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}
		}
		ofPopStyle();
	};


};