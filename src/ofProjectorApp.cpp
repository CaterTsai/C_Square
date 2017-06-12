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
}


//--------------------------------------------------------------
void ofProjectorApp::keyPressed(int key)
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
		squareMgr::GetInstance()->enableSquareControl(1);
		break;
	}
	case 'e':
	{
		squareMgr::GetInstance()->disableSquareControl();
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

