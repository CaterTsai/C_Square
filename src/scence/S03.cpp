#include "S03.h"
#include "view.h"
S03::S03()
	:SBase(eS03)
{
	initView();
}

#pragma region View
//-------------------------------------
void S03::initView()
{
	_viewList.push_back(ofPtr<VS03_1>(new VS03_1("view/s3/1.xml")));
}

//-------------------------------------
void S03::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S03::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



