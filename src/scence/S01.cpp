#include "S01.h"
#include "view.h"
S01::S01()
	:SBase(eS01)
{
	initView();
}

#pragma region View
//-------------------------------------
void S01::initView()
{
}

//-------------------------------------
void S01::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S01::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



