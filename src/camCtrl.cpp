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
void camCtrl::stopAll()
{
	for (auto& iter : _squareCams)
	{
		iter.stop();
	}
	_canvasCam.stop();
}

//--------------------------------------------------------------
ofEasyCam & camCtrl::getSquareCam(int id)
{
	return	_squareCams[id]._cam;
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
