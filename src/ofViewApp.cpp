#include "ofViewApp.h"

//--------------------------------------------------------------
void ofViewApp::setup()
{
	ofBackground(23, 24, 26);
	//ofDisableArbTex();
	squareMgr::GetInstance()->setup();
	ofSetFrameRate(60);
	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofViewApp::update()
{
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	_testScence.update(delta);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofViewApp::draw()
{
	ofSetBackgroundColor(0);
	_testScence.draw();

	squareMgr::GetInstance()->displayEachUnit(ofVec2f(0, 0), 1024);
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
	case 't':
	{
		_testScence.trigger();
		break;
	}
	}

	
}

//--------------------------------------------------------------
void ofViewApp::mouseDragged(int x, int y, int button)
{
	squareMgr::GetInstance()->mouseDraggedFromView(x, y);
}
