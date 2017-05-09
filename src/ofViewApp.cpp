#include "ofViewApp.h"

//--------------------------------------------------------------
void ofViewApp::setup()
{
	ofBackground(0);

	_test1.loadImage("images/test1.jpg");
	_test2.loadImage("images/test2.jpg");

	ofDisableArbTex();
	
	squareMgr::GetInstance()->setGroupSize(_test2.getWidth(), _test2.getHeight());
}

//--------------------------------------------------------------
void ofViewApp::update()
{
	squareMgr::GetInstance()->updateOnUnitBegin(0);
	{
		_test1.draw(0, 0);
	}
	squareMgr::GetInstance()->updateOnUnitEnd(0);

	squareMgr::GetInstance()->updateByGroup(_test2);
}

//--------------------------------------------------------------
void ofViewApp::draw()
{
	ofSetBackgroundColor(0);

	ofSetColor(255);
	_test2.draw(0, 0);

	squareMgr::GetInstance()->displayUnitOnGroup(ofVec2f(0, 0));
	squareMgr::GetInstance()->displayEachUnit(ofVec2f(0, _test2.getHeight()), cViewWindowWidth * 0.5);
}

//--------------------------------------------------------------
void ofViewApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void ofViewApp::mouseDragged(int x, int y, int button)
{
	squareMgr::GetInstance()->mouseDraggedFromView(x, y);
}
