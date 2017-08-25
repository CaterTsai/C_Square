#include "S11.h"
#include "view.h"
S11::S11()
	:SBase(eS11)
{
	initView();
}

#pragma region View
//-------------------------------------
void S11::initView()
{
	_viewList.push_back(ofPtr<VS11_1>(new VS11_1("view/s11/1.xml")));
}

//-------------------------------------
void S11::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S11::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



