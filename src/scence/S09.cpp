#include "S09.h"

S09::S09()
	:SBase(eS09)
{
	initView();
}

//-------------------------------------
void S09::update(float delta)
{
	if (!_isStart)
	{
		return;
	}

	for (auto& iter : _viewList)
	{
		iter->update(delta);
	}

}

//-------------------------------------
void S09::draw()
{
	if (!_isStart)
	{
		return;
	}

	_viewList[_viewID]->draw(0, 0);
}

//-------------------------------------
void S09::start()
{

	_isStart = true;
}

//-------------------------------------
void S09::stop()
{
	_isStart = false;
}

//-------------------------------------
void S09::control(eCtrlType ctrl, int value)
{
	if (ctrl == eCtrl_ViewNext)
	{
		setView( (_viewID + 1) % _viewList.size());
	}
	else
	{

	}
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



