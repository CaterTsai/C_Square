#pragma once

#include "baseView.h"

class VSTest02 : public baseView
{
public:
	VSTest02(string path)
		:baseView(path)
	{
		_img.loadImage("giraffe.jpg");
	}

	void draw(int width, int height) override
	{
		ofPushStyle();
		ofEnableDepthTest();
		{
			squareMgr::GetInstance()->updateByGroup(_img);
		}
		ofPopStyle();
	};

private:
	ofImage	_img;
};