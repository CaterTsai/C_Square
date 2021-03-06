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
	_pos += _vec * delta;
	
	_vec += -0.1 * _pos * delta;
	//_vec += force * delta;

	_vec.limit(1.0);

	
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

	//updateCenter(delta);

	for (auto& iter : _ballList)
	{
		ofVec3f desired = (_forceCenter - iter._pos).normalize();
		desired *= _forceValue;
		ofVec3f steering = desired - iter._vec;
		iter.update(delta, steering);
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
		
		if (_drawGrid)
		{
			_mcubes.drawGrid();
		}
		if (_drawMetaball)
		{
			_mcubes.draw(_drawWireframe);
		}
		if (_drawBall)
		{
			drawBall();
		}
		
		ofDisableDepthTest();
	}
	ofPopStyle();
}

//-------------------------------------
void DMetaBall3D::start()
{
	_isStart = true;
	_forceCenter.set(0);
	_forceVec.set(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5));
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
	ofColor red(200, 150, 150);
	for (int i = num; i > 0; i--)
	{
		ofColor c = red;
		c.setHueAngle(ofRandom(0, 360));
		ball newBall(
			ofVec3f(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5)),
			ofVec3f(ofRandom(-0.2, 0.2), ofRandom(-0.2, 0.2), ofRandom(-0.2, 0.2)),
			c,
			0.1
		);
		_ballList.push_back(newBall);
	}
}

//-------------------------------------
void DMetaBall3D::updateCenter(float delta)
{
	_forceCenter += _forceVec * delta;
	_forceVec += -0.5 * _forceCenter * delta;
	_forceVec.limit(0.5);
}


