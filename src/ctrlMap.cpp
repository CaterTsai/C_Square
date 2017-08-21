#include "ctrlMap.h"

//--------------------------------------------------------------
void ctrlMap::initKey2Ctrl()
{
	key2Ctrl['s'] = eCtrl_Start;
	key2Ctrl['d'] = eCtrl_Stop;
	key2Ctrl['w'] = eCtrl_NextScence;
	key2Ctrl['q'] = eCtrl_PrevScence;

	key2Ctrl['y'] = eCtrl_Filter1;
	key2Ctrl['u'] = eCtrl_Filter2;
	key2Ctrl['i'] = eCtrl_Filter3;
	key2Ctrl['h'] = eCtrl_Filter4;
	key2Ctrl['j'] = eCtrl_Filter5;
	key2Ctrl['k'] = eCtrl_Filter6;
	key2Ctrl['n'] = eCtrl_Filter7;
	key2Ctrl['m'] = eCtrl_Filter8;
	key2Ctrl[','] = eCtrl_Filter9;
	key2Ctrl['.'] = eCtrl_DisableAllFilter;
	key2Ctrl['/'] = eCtrl_ChangeFilterTarget;

	key2Ctrl['['] = eCtrl_DisplayEach;
	key2Ctrl[']'] = eCtrl_DisplayGroup;
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