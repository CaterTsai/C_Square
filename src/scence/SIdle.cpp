#include "SIdle.h"
#include "view.h"
SIdle::SIdle()
	:SBase(eSIdle)
{
	initView();
}


#pragma region View
//-------------------------------------
void SIdle::initView()
{
	_viewList.push_back(ofPtr<VSIdle>(new VSIdle("view/sIdle/1.xml")));
}

//-------------------------------------
void SIdle::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[SIdle::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



