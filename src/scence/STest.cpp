#include "STest.h"
#include "view.h"
STest::STest()
	:SBase(eSTest)
{
	initView();
	_img.loadImage("giraffe.jpg");
}

//-------------------------------------
void STest::update(float delta)
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
void STest::draw()
{
	if (!_isStart)
	{
		return;
	}

	_viewList[_viewID]->draw(0, 0);
}

//-------------------------------------
void STest::start()
{

	_isStart = true;
}

//-------------------------------------
void STest::stop()
{
	_isStart = false;
}

//-------------------------------------
void STest::control(eCtrlType ctrl, int value)
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
void STest::initView()
{

}

//-------------------------------------
void STest::setView(int id)
{
	if (id < 0 || id >= _viewList.size())
	{
		ofLog(OF_LOG_ERROR, "[STest::setView]id out of range");
		return;
	}

	_viewList[id]->set();
	_viewID = id;
}
#pragma endregion



