#include "STest.h"

//-------------------------------------
void STest::update(float delta)
{
	if (!_isStart)
	{
		return;
	}
	_life.update(delta);
	//_eca.update(delta);
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
		_life.draw(0, 0, rect.width, rect.height);
		//_eca.draw(0, 0, rect.width, rect.height);
		squareMgr::GetInstance()->updateOnUnitEnd(0);
	}
	ofPopStyle();
}

//-------------------------------------
void STest::start()
{
	_isStart = true;
	_life.start();
	//_eca.start();

}

//-------------------------------------
void STest::stop()
{
	_isStart = false;
	_life.stop();
	//_eca.stop();
	
}
