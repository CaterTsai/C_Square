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
	_viewList.push_back(ofPtr<VS09_1>(new VS09_1("view/s9/1.xml")));
	_viewList.push_back(ofPtr<VS09_2>(new VS09_2("view/s9/2.xml")));
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



