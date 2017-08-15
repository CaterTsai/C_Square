#include "SIdle.h"

SIdle::SIdle()
	:SBase(eSIdle)
{
	initView();
}

//-------------------------------------
void SIdle::update(float delta)
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
void SIdle::draw()
{
	if (!_isStart)
	{
		return;
	}

	_viewList[_viewID]->draw(0, 0);
}

//-------------------------------------
void SIdle::start()
{

	_isStart = true;
}

//-------------------------------------
void SIdle::stop()
{
	_isStart = false;
}

//-------------------------------------
void SIdle::control(eCtrlType ctrl, int value)
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
void SIdle::initView()
{
}

//-------------------------------------
void SIdle::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[SIdle::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



