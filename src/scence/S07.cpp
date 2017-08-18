#include "S07.h"
#include "view.h"
S07::S07()
	:SBase(eS07)
{
	initView();
}


#pragma region View
//-------------------------------------
void S07::initView()
{
	_viewList.push_back(ofPtr<VS07_1>(new VS07_1("view/s7/1.xml")));
}

//-------------------------------------
void S07::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S07::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



