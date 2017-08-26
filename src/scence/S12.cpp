#include "S12.h"
#include "view.h"
S12::S12()
	:SBase(eS12)
{
	initView();
}

#pragma region View
//-------------------------------------
void S12::initView()
{
	_viewList.push_back(ofPtr<VS12_1>(new VS12_1("view/s12/1.xml")));
	_viewList.push_back(ofPtr<VS12_2>(new VS12_2("view/s12/2.xml")));
	_viewList.push_back(ofPtr<VS12_3>(new VS12_3("view/s12/3.xml")));
	_viewList.push_back(ofPtr<VS12_4>(new VS12_4("view/s12/4.xml")));
	_viewList.push_back(ofPtr<VS12_5>(new VS12_5("view/s12/5.xml")));
}

//-------------------------------------
void S12::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S01::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



