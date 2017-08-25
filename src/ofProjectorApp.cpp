#include "ofProjectorApp.h"

//--------------------------------------------------------------
void ofProjectorApp::setup()
{
	ofBackground(0);
	_coverAlpha = 0;

	midiCtrl::GetInstance()->init();
	midiCtrl::GetInstance()->addListener(this);
}

//--------------------------------------------------------------
void ofProjectorApp::update()
{

}

//--------------------------------------------------------------
void ofProjectorApp::draw()
{	
	squareMgr::GetInstance()->drawToProjection();
	
	ofPushStyle();
	ofSetColor(0, 255 - _coverAlpha);
	ofFill();
	ofDrawRectangle(0, 0, cProjectionWindowWidth, cProjectionWindowHeight);
	ofPopStyle();
}


//--------------------------------------------------------------
void ofProjectorApp::keyPressed(int key)
{
	switch (key)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	{
		int id = key - '1';
		squareMgr::GetInstance()->enableSquareControl(id);
		break;
	}
	case '0':
	{
		squareMgr::GetInstance()->disableSquareControl();
		break;
	}
	case 'z':
	{
		squareMgr::GetInstance()->saveConfig("config/_squareConfig.xml");
		break;
	}
	}
}

//--------------------------------------------------------------
void ofProjectorApp::mousePressed(int x, int y, int button)
{
	squareMgr::GetInstance()->mousePressedFromProjector(x, y);
}

//--------------------------------------------------------------
void ofProjectorApp::mouseDragged(int x, int y, int button)
{
	squareMgr::GetInstance()->mouseDraggedFromProjector(x, y);
}

//--------------------------------------------------------------
void ofProjectorApp::mouseReleased(int x, int y, int button)
{
	squareMgr::GetInstance()->mouseReleasedFromProject(x, y);
}

//--------------------------------------------------------------
void ofProjectorApp::newMidiMessage(ofxMidiMessage & msg)
{
	auto type = ctrlMap::GetInstance()->midi2Ctrl[msg.control];
	if (type == eMidiSlider1)
	{
		_coverAlpha = ofMap(msg.value, 0, 127, 0, 255);
	}
}

