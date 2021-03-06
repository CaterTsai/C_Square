#include "S02.h"
#include "view.h"
S02::S02()
	:SBase(eS02)
{
	initView();
}

#pragma region View
//-------------------------------------
void S02::initView()
{
	_viewList.push_back(ofPtr<VS02_1>(new VS02_1("view/s2/1.xml")));
}

//-------------------------------------
void S02::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S02::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



