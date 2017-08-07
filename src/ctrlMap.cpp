#include "ctrlMap.h"

//--------------------------------------------------------------
void ctrlMap::initKey2Ctrl()
{
	key2Ctrl['s'] = eCtrl_Start;
	key2Ctrl['t'] = eCtrl_ViewTrigger1;
}

//--------------------------------------------------------------
void ctrlMap::initMidi2Ctrl()
{
	midi2Ctrl[0] = eCtrl_Start;
	midi2Ctrl[1] = eCtrl_ViewTrigger1;
}

//--------------------------------------------------------------
ctrlMap::ctrlMap()
{
	initKey2Ctrl();
	initMidi2Ctrl();
}

//--------------------------------------------------------------
ctrlMap* ctrlMap::pInstance = 0;
ctrlMap* ctrlMap::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new ctrlMap();
	}
	return pInstance;
}

//--------------------------------------------------------------
void ctrlMap::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}