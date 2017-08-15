#include "ofProjectorApp.h"

//--------------------------------------------------------------
void ofProjectorApp::setup()
{
	ofBackground(0);
	ofDisableArbTex();
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
	ofSetColor(0, sCoverAlpha);
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

