#include "DMoveRect.h"

//----------------------------------
void DMoveRect::update(float delta)
{
	CHECK_START();
}

//----------------------------------
void DMoveRect::draw(int id, int x, int y, int w, int h)
{
	CHECK_START();
}

//----------------------------------
void DMoveRect::start()
{
	_isStart = true;
}

//----------------------------------
void DMoveRect::stop()
{
	_isStart = false;
}

//----------------------------------
void DMoveRect::trigger()
{
}

//----------------------------------
void DMoveRect::setGroupNum(int num)
{
	_groupNum = num;
}
