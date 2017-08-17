#include "S04.h"
#include "view.h"
S04::S04()
	:SBase(eS04)
{
	initView();
}


#pragma region View
//-------------------------------------
void S04::initView()
{
	_viewList.push_back(ofPtr<VS04_1>(new VS04_1("view/s4/1.xml")));
}

//-------------------------------------
void S04::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S04::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



