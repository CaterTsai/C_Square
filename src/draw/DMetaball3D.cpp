#include "DMetaBall3D.h"

#pragma region ball
//-------------------------------------
DMetaBall3D::ball::ball(ofVec3f pos, ofVec3f vec, ofColor c, float size)
	:_pos(pos)
	,_vec(vec)
	,_color(c)
	,_size(size)
{}

//-------------------------------------
void DMetaBall3D::ball::update(float delta)
{
	_pos += _vec * delta;
	checkLimit(_pos.x, _vec.x);
	checkLimit(_pos.y, _vec.y);
	checkLimit(_pos.z, _vec.z);
}

//-------------------------------------
void DMetaBall3D::ball::checkLimit(float & p, float & v)
{
	if (p < -0.5)
	{
		p = -0.5;
		v = -v;
	}
	else if (p > 0.5)
	{
		p = 0.5;
		v = -v;
	}
}

#pragma endregion

//-------------------------------------
void DMetaBall3D::update(float delta)
{
	CHECK_START();

	for (auto& iter_ : _ballList)
	{
		iter_.update(delta);
	}
}

//-------------------------------------
void DMetaBall3D::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	for (auto& iter_ : _ballList)
	{
	}
	ofPopStyle();
}

//-------------------------------------
void DMetaBall3D::start()
{
	_isStart = true;
}

//-------------------------------------
void DMetaBall3D::stop()
{
	_isStart = false;
}

//-------------------------------------
void DMetaBall3D::setBaseSize(float baseSize)
{
	_baseSize = baseSize;
}

//-------------------------------------
void DMetaBall3D::initMetaBall()
{
}


