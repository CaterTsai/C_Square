#include "S04.h"

S04::S04()
	:SBase(eS04)
{
	initView();
}

//-------------------------------------
void S04::update(float delta)
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
void S04::draw()
{
	if (!_isStart)
	{
		return;
	}

	_viewList[_viewID]->draw(0, 0);
}

//-------------------------------------
void S04::start()
{
	_isStart = true;
	_viewID = 0;
	_viewList[_viewID]->start();
}

//-------------------------------------
void S04::stop()
{
	_isStart = false;
}

//-------------------------------------
void S04::control(eCtrlType ctrl, int value)
{
	if (ctrl == eCtrl_Start)
	{
		start();
	}
	else if (ctrl == eCtrl_ViewNext)
	{
		setView( (_viewID + 1) % _viewList.size());
	}
	else
	{
		if (ctrl > eCtrl_View && ctrl < eCtrl_ViewNum)
		{
			_viewList[_viewID]->control(ctrl, value);
		}
	}
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



