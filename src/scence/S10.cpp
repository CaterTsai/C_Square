#include "S10.h"
#include "view.h"
S10::S10()
	:SBase(eS10)
{
	initView();
}

#pragma region View
//-------------------------------------
void S10::initView()
{

}

//-------------------------------------
void S10::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S10::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



