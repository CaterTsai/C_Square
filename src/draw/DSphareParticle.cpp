#include "DSphareParticle.h"

#pragma region particle
void DSphareParticle::particle::set(float t, float p, float vt, float vp)
{
	_t = t;
	_p = p;
	_vt = vt;
	_vp = vp;
}
//-------------------------------------
void DSphareParticle::particle::update(float delta)
{
	_t += _vt * delta;
	_p += _vp * delta;
	_t = (_t >= TWO_PI) ? _t - TWO_PI : _t;
	_p = (_p >= TWO_PI) ? _p - TWO_PI : _p;

	_pos.x = sin(_t) * cos(_p);
	_pos.y = sin(_t) * sin(_p);
	_pos.z = cos(_t);
}

#pragma endregion

//-------------------------------------
void DSphareParticle::update(float delta)
{
	CHECK_START();
	for (auto& iter : _particleList)
	{
		iter.update(delta);
		
	}
	computeNear();
}

//-------------------------------------
void DSphareParticle::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255);
	_cam.begin();
	{
		drawNear(w);
		for (auto& iter : _particleList)
		{
			auto p = iter.getPos() * w;
			ofDrawSphere(p, 5);
		}
		
	}
	_cam.end();
	ofPopStyle();
}

//-------------------------------------
void DSphareParticle::start()
{
	_isStart = true;
	generateParticle();
}

//-------------------------------------
void DSphareParticle::stop()
{
	_isStart = false;
}

//-------------------------------------
void DSphareParticle::generateParticle()
{
	ofSeedRandom();

	for (int i = 0; i < cDPNumber; i++)
	{
		_particleList[i].set(
			ofRandom(TWO_PI)
			,ofRandom(TWO_PI)
			,ofRandom(cDPSpeedMin, cDPSpeedMax)
			,ofRandom(cDPSpeedMin, cDPSpeedMax)
		);
	}
}

//-------------------------------------
void DSphareParticle::drawNear(int size)
{
	for (auto& iter : _particleList)
	{
		if (iter.haveNear())
		{
			ofDrawLine(iter.getPos() * size, iter.getNearPos() * size);
		}
	}
}

//-------------------------------------
void DSphareParticle::computeNear()
{
	for (int i = 0; i < cDPNumber; i++)
	{
		_particleList[i].resetNear();
		float min = cDPNearLimit;
		for (int j = 0; j < cDPNumber; j++)
		{
			if (i == j)
			{
				continue;
			}
			auto dist = _particleList[i].getPos().distance(_particleList[j].getPos());
			if (dist < min)
			{
				min = dist;
				_particleList[i].setNearPos(_particleList[j].getPos());
				break;
			}
		}
	}
}
