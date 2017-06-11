#pragma once

#include "constParameter.h"
#include "scence.h"

class ofViewApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);

private:
	float _mainTimer;


//Scence
private:
	STest	_testScence;

};