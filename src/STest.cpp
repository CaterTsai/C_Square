#include "STest.h"

//-------------------------------------
void STest::update(float delta)
{
	if (!_isStart)
	{
		return;
	}

}

//-------------------------------------
void STest::draw()
{
	if (!_isStart)
	{
		return;
	}

	ofPushStyle();
	{
		auto rect = squareMgr::GetInstance()->getUnitRect(0);
		squareMgr::GetInstance()->updateOnUnitBegin(0);
		squareMgr::GetInstance()->updateOnUnitEnd(0);
	}
	ofPopStyle();
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
