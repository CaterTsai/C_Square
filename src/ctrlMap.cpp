#include "ctrlMap.h"

//--------------------------------------------------------------
void ctrlMap::initKey2Ctrl()
{
	key2Ctrl['s'] = eCtrl_Start;
	key2Ctrl['v'] = eCtrl_ViewNext;
	key2Ctrl['1'] = eCtrl_ViewTrigger1;
	key2Ctrl['2'] = eCtrl_ViewTrigger2;
	key2Ctrl['3'] = eCtrl_ViewTrigger3;
	key2Ctrl['4'] = eCtrl_ViewTrigger4;
	key2Ctrl['5'] = eCtrl_ViewTrigger5;
	key2Ctrl['6'] = eCtrl_ViewTrigger6;
	key2Ctrl['7'] = eCtrl_ViewTrigger7;
	key2Ctrl['8'] = eCtrl_ViewTrigger8;
	key2Ctrl['9'] = eCtrl_ViewTrigger9;
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