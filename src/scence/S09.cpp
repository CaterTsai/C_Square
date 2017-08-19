#include "S09.h"
#include "view.h"
S09::S09()
	:SBase(eS09)
{
	initView();
}


#pragma region View
//-------------------------------------
void S09::initView()
{

}

//-------------------------------------
void S09::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S09::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



