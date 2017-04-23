#pragma once

#include "constParameter.h"
#include "squareMgr.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void drawView(ofEventArgs & args);

	void keyPressed(int key);

private:
	ofImage _test1, _test2;
#pragma region squareMgr
public:
	void setupSquareMgr();	

#pragma endregion



};
