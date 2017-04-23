#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(0);

	_test1.loadImage("images/test1.jpg");
	_test2.loadImage("images/test2.jpg");

	ofDisableArbTex();
	squareMgr::GetInstance()->setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
	squareMgr::GetInstance()->updateOnUnitBegin(0);
	{
		_test1.draw(0, 0);
	}
	squareMgr::GetInstance()->updateOnUnitEnd(0);

	squareMgr::GetInstance()->updateByGroup(_test2);
}

//--------------------------------------------------------------
void ofApp::draw()
{	
	squareMgr::GetInstance()->drawToProjection();
}

//--------------------------------------------------------------
void ofApp::drawView(ofEventArgs & args)
{
	ofSetBackgroundColor(0);
	
	ofSetColor(255);
	_test2.draw(0, 0);

	squareMgr::GetInstance()->drawOnGroup(ofVec2f(0, 0));
	squareMgr::GetInstance()->drawEachUnit(ofVec2f(0, _test2.getHeight()), cViewWindowWidth * 0.5);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
	case 'q':
	{
		squareMgr::GetInstance()->enableSquareControl(0);
		break;
	}
	case 'w':
	{
		squareMgr::GetInstance()->disableSquareControl();
		break;
	}
	}
}

#pragma region squareMgr
//--------------------------------------------------------------
void ofApp::setupSquareMgr()
{
	squareMgr::GetInstance()->setup();
}
#pragma endregion
