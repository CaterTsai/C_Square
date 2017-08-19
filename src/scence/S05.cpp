#include "S05.h"
#include "view.h"
S05::S05()
	:SBase(eS05)
{
	initView();
}

#pragma region View
//-------------------------------------
void S05::initView()
{
}

//-------------------------------------
void S05::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S05::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



