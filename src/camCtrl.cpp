#include "camCtrl.h"

//--------------------------------------------------------------
void camCtrl::update(float delta)
{
	for (auto& iter : _squareCams)
	{
		iter.update(delta);
	}
	_canvasCam.update(delta);
}

//--------------------------------------------------------------
void camCtrl::displayPos(ofVec2f pos)
{
	ostringstream ss;
	for (int i = 0; i < cSquareNum; i++)
	{
		ofVec3f posC = _squareCams[i]._cam.getGlobalPosition();
		
		ss << "cam " + ofToString(i);
		ss << " = (" + ofToString(posC.x);
		ss << "," + ofToString(posC.y);
		ss << "," + ofToString(posC.z);
		ss << ")\n";
		
	}
	ofVec3f posC = _canvasCam._cam.getGlobalPosition();
	ss << "cam canvas";
	ss << " = (" + ofToString(posC.x);
	ss << "," + ofToString(posC.y);
	ss << "," + ofToString(posC.z);
	ss << ")\n";
	ofDrawBitmapStringHighlight(ss.str(), pos);
}

//--------------------------------------------------------------
void camCtrl::stopAll()
{
	for (auto& iter : _squareCams)
	{
		iter.stop();
	}
	_canvasCam.stop();
}

//--------------------------------------------------------------
void camCtrl::reset()
{
	for (auto& iter : _squareCams)
	{
		iter.reset();
	}
	_canvasCam.reset();
}

//--------------------------------------------------------------
ofEasyCam & camCtrl::getSquareCam(int id)
{
	return	_squareCams[id]._cam;
}

//--------------------------------------------------------------
ofEasyCam & camCtrl::getCanvasCam()
{
	return _canvasCam._cam;
}

//--------------------------------------------------------------
camCtrl* camCtrl::pInstance = 0;
camCtrl* camCtrl::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new camCtrl();
	}
	return pInstance;
}

//--------------------------------------------------------------
void camCtrl::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
