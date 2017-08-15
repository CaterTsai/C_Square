#include "ofViewApp.h"

//--------------------------------------------------------------
void ofViewApp::setup()
{
	ofBackground(23, 24, 26);
	ofSetCircleResolution(60);
	//ofEnableSmoothing();
	//ofDisableArbTex();
	
	initScence();

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
	_scenceMgr[_nowScence]->update(delta);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofViewApp::draw()
{
	ofSetBackgroundColor(0);
	_scenceMgr[_nowScence]->draw();

	squareMgr::GetInstance()->displayEachUnit(ofVec2f(0, 0), 1024);
}

//--------------------------------------------------------------
void ofViewApp::keyPressed(int key)
{	
	_scenceMgr[_nowScence]->control(ctrlMap::GetInstance()->key2Ctrl[key]);
}

//--------------------------------------------------------------
void ofViewApp::mouseDragged(int x, int y, int button)
{
	squareMgr::GetInstance()->mouseDraggedFromView(x, y);
}

//--------------------------------------------------------------
void ofViewApp::initScence()
{
	_scenceMgr.push_back(ofPtr<SIdle>(new SIdle()));
	_scenceMgr.push_back(ofPtr<S01>(new S01()));
	_scenceMgr.push_back(ofPtr<S02>(new S02()));
	_scenceMgr.push_back(ofPtr<S03>(new S03()));
	_scenceMgr.push_back(ofPtr<S04>(new S04()));
	_scenceMgr.push_back(ofPtr<S05>(new S05()));
	_scenceMgr.push_back(ofPtr<S06>(new S06()));
	_scenceMgr.push_back(ofPtr<S07>(new S07()));
	_scenceMgr.push_back(ofPtr<S08>(new S08()));
	_scenceMgr.push_back(ofPtr<S09>(new S09()));
	_scenceMgr.push_back(ofPtr<S10>(new S10()));
	_scenceMgr.push_back(ofPtr<S11>(new S11()));

	_nowScence = eS04;
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
