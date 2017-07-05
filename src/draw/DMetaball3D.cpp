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
void DMetaBall3D::ball::update(float delta, ofVec3f force)
{
	_vec += force * delta;
	_vec.limit(2.0);
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

	if (abs(_forceValue) > 1.0)
	{
		_forceValue *= 0.9;
	}

	_mcubes.resetGrid();
	for (auto& iter : _ballList)
	{
		ofVec3f desired = (_forceCenter - iter._pos);
		ofVec3f steering = (desired.normalized() - iter._vec) * _forceValue;
		iter.update(delta, steering.limited(1.0));
		_mcubes.addMetaBall(iter._pos * _baseSize, iter._size * _baseSize, iter._color);
	}
	_mcubes.update(0.7 + _ballList.size() * 0.1, true);
	
}

//-------------------------------------
void DMetaBall3D::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	{
		ofEnableDepthTest();
		_mcubes.drawGrid();
		_mcubes.draw(true);
		drawBall();
		ofDisableDepthTest();
	}
	ofPopStyle();
}

//-------------------------------------
void DMetaBall3D::start()
{
	_isStart = true;
	initMetaBall();
}

//-------------------------------------
void DMetaBall3D::stop()
{
	_isStart = false;
}

//-------------------------------------
void DMetaBall3D::trigger()
{
	CHECK_START();
	//addBallElement(1);
	_forceValue = -_forceValue;
}

//-------------------------------------
void DMetaBall3D::setBaseSize(float baseSize)
{
	_baseSize = baseSize;
}

//-------------------------------------
void DMetaBall3D::initMetaBall()
{
	_ballList.clear();
	_mcubes.setGrid(_baseSize);
	addBallElement(5);
}

//-------------------------------------
void DMetaBall3D::drawBall()
{
	ofPushStyle();
	for (auto& iter : _ballList)
	{
		ofSetColor(iter._color);
		auto pos = iter._pos * _baseSize;
		ofDrawSphere(pos, iter._size * _baseSize);
	}
	ofPopStyle();
}

//-------------------------------------
void DMetaBall3D::addBallElement(int num)
{
	ofColor red(255, 0, 0);
	for (int i = num; i > 0; i--)
	{
		ofColor c = red;
		c.setHueAngle(ofRandom(0, 360));
		ball newBall(
			ofVec3f(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5)),
			ofVec3f(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5)),
			c,
			0.1
		);
		_ballList.push_back(newBall);
	}
}


