#pragma once

#include "constParameter.h"
#include "squareMgr.h"

class ofProjectorApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

private:
	int _coverAlpha;
};
