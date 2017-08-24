#pragma once

#include "constParameter.h"
#include "lightStruct.h"
#include "sender.h"

class lightCtrl
{
public:
	lightCtrl()
	{}

	void setType(int type);
	void enable();
	void disable();

	//Button Event
	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e);

	void idleLight();

private:
	void playEvent(int id);
	void releaseEvent(int id);

private:
	int _type; //0 or 1
};