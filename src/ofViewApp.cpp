#include "ofViewApp.h"

//--------------------------------------------------------------
void ofViewApp::setup()
{
	ofBackground(23, 24, 26);
	ofSetCircleResolution(60);
	//ofEnableSmoothing();
	//ofDisableArbTex();
	
	//Singleton
	squareMgr::GetInstance()->setup("config/_squareConfig.xml");
	postFilter::GetInstance()->init(200, 200, 1280, 720);

	ofSetFrameRate(60);
	
	
	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofViewApp::update()
{
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	camCtrl::GetInstance()->update(delta);
	_scence04.update(delta);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofViewApp::draw()
{
	ofSetBackgroundColor(0);
	_scence04.draw();

	squareMgr::GetInstance()->displayEachUnit(ofVec2f(0, 0), 1024);
}

//--------------------------------------------------------------
void ofViewApp::keyPressed(int key)
{	
	_scence04.control(ctrlMap::GetInstance()->key2Ctrl[key]);
}

//--------------------------------------------------------------
void ofViewApp::mouseDragged(int x, int y, int button)
{
	squareMgr::GetInstance()->mouseDraggedFromView(x, y);
}

//--------------------------------------------------------------
void ofViewApp::setupSoundStream()
{
	_soundStream.setup(this, 0, 2, 44100, cBufferSize, 4);
}

//--------------------------------------------------------------
void ofViewApp::audioIn(float * input, int bufferSize, int nChannels)
{
}
