#include "S08.h"

S08::S08()
	:SBase(eS08)
{
	initView();
}

//-------------------------------------
void S08::update(float delta)
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
void S08::draw()
{
	if (!_isStart)
	{
		return;
	}

	_viewList[_viewID]->draw(0, 0);
}

//-------------------------------------
void S08::start()
{

	_isStart = true;
}

//-------------------------------------
void S08::stop()
{
	_isStart = false;
}

//-------------------------------------
void S08::control(eCtrlType ctrl, int value)
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
void S08::initView()
{
}

//-------------------------------------
void S08::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[S08::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



