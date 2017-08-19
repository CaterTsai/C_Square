#include "DStar.h"

//-------------------------------------
void DStar::update(float delta)
{
	CHECK_START();

	updateStar(delta);

	_timer -= delta;
	if (_timer <= 0.0f)
	{
		addStar((rand() % 40 + 10));
		_timer = ofRandom(cDStarAddMinT, cDStarAddMaxT);;
	}
}

//-------------------------------------
void DStar::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofSetColor(255);
	for (auto& iter : _starList)
	{
		ofDrawSphere(iter.pos.x * w, iter.pos.y * w, iter.pos.z * h * 5, 10);
	}
}

//-------------------------------------
void DStar::start()
{
	_starList.clear();
	_isStart = true;
	_timer = ofRandom(cDStarAddMinT, cDStarAddMaxT);

}

//-------------------------------------
void DStar::stop()
{
	_isStart = false;
}

//-------------------------------------
void DStar::updateStar(float delta)
{
	auto iter = _starList.begin();
	while (iter != _starList.end())
	{
		iter->pos.z += iter->v * delta;
		if (_forward && iter->pos.z < -cDStarMoveMax)
		{
			iter = _starList.erase(iter);
		}
		else if (!_forward && iter->pos.z > cDStarMovMin)
		{
			iter = _starList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

//-------------------------------------
void DStar::addStar(int num)
{
	for (int i = num; i > 0; i--)
	{
		if (_starList.size() > cDStarMaxNum)
		{
			break;
		}
		_starList.push_back(star(_forward));
	}
}
