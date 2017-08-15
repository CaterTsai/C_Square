#include "S05.h"

S05::S05()
	:SBase(eS05)
{
	initView();
}

//-------------------------------------
void S05::update(float delta)
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
void S05::draw()
{
	if (!_isStart)
	{
		return;
	}

	_viewList[_viewID]->draw(0, 0);
}

//-------------------------------------
void S05::start()
{

	_isStart = true;
}

//-------------------------------------
void S05::stop()
{
	_isStart = false;
}

//-------------------------------------
void S05::control(eCtrlType ctrl, int value)
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
void S05::initView()
{
}

//-------------------------------------
void S05::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S05::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



