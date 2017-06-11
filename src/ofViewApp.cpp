#include "ofViewApp.h"

//--------------------------------------------------------------
void ofViewApp::setup()
{
	ofBackground(0);
	ofDisableArbTex();
	ofSetFrameRate(60);
	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofViewApp::update()
{
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	_testScence.update(delta);
}

//--------------------------------------------------------------
void ofViewApp::draw()
{
	ofSetBackgroundColor(0);
	_testScence.draw();

	squareMgr::GetInstance()->displayEachUnit(ofVec2f(0, 0), cViewWindowWidth * 0.5);
}

//--------------------------------------------------------------
void ofViewApp::keyPressed(int key)
{
	switch (key)
	{
	case 's':
	{
		_testScence.start();
		break;
	}
	}

	
}

//--------------------------------------------------------------
void ofViewApp::mouseDragged(int x, int y, int button)
{
	squareMgr::GetInstance()->mouseDraggedFromView(x, y);
}
