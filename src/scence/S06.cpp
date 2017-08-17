#include "S06.h"
#include "view.h"
S06::S06()
	:SBase(eS06)
{
	initView();
}

#pragma region View
//-------------------------------------
void S06::initView()
{
	_viewList.push_back(ofPtr<VS06_1>(new VS06_1("view/s6/1.xml")));
}

//-------------------------------------
void S06::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S06::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



