#pragma once

#include "constParameter.h"
#include "squareMgr.h"

class ofViewApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
private:
	ofImage _test1, _test2;
};