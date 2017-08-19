#include "S08.h"
#include "view.h"

S08::S08()
	:SBase(eS08)
{
	initView();
}

#pragma region View
//-------------------------------------
void S08::initView()
{
	_viewList.push_back(ofPtr<VS08_1>(new VS08_1("view/s8/1.xml")));
	_viewList.push_back(ofPtr<VS08_2>(new VS08_2("view/s8/2.xml")));
}

//-------------------------------------
void S08::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S08::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



