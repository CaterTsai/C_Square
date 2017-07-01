#include "DSphareParticle.h"

#pragma region particle
void DSphareParticle::particle::set(float t, float p, float vt, float vp, float maxT, float minT)
{
	_t = t;
	_p = p;
	_vt = vt;
	_vp = vp;
	_maxT = maxT;
	_minT = minT;

	_pos.x = sin(_t) * cos(_p);
	_pos.y = cos(_t); 
	_pos.z = sin(_t) * sin(_p);
}

//-------------------------------------
void DSphareParticle::particle::setAmt(float amt)
{
	_amt = amt;
}

//-------------------------------------
void DSphareParticle::particle::update(float delta, float baseSize)
{
	if ( _maxT - _t < cDPThetaLimit || _t - _minT < cDPThetaLimit)
	{
		_vt = -_vt;
	}

	_t += _vt * delta;
	_p += _vp * delta;
	
	if (_t > PI || _t < 0)
	{
		_t = (_t > PI)?TWO_PI - _t:-_t;
		_vt = -_vt;
		_p += PI;
	}
	_p = (_p >= TWO_PI) ? _p - TWO_PI : (_p < 0) ? _p + TWO_PI : _p;
	

	_pos.x = sin(_t) * cos(_p);
	_pos.y = cos(_t);
	_pos.z = sin(_t) * sin(_p);
	
	if (_amt - 1.0 > 0.01)
	{
		_amt *= 0.98;
	}
	else if (1.0 - _amt > 0.01)
	{
		_amt *= 1 + (1 - 0.98);
	}
	else
	{
		_amt = 1.0;
	}
	
	_pos *= (baseSize * _amt);
}


#pragma endregion

//-------------------------------------
void DSphareParticle::update(float delta)
{
	CHECK_START();
	for (int i = 0; i < _particleList.size(); i++)
	{
		_particleList[i].update(delta, _baseSize);
		_tri.setVertex(i, _particleList[i]._pos);
	}
	if (ofGetFrameNum() % 5 == 0)
	{
		computeTri();
	}
	
}

//-------------------------------------
void DSphareParticle::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255);
	{
		for (auto& iter : _particleList)
		{
			ofDrawSphere(iter._pos, 5);
		}
		
		if (_tri.hasIndices())
		{
			ofSetColor(255, 150);
			_tri.drawFaces();
		}
		
		ofSetColor(255);
		_tri.drawWireframe();
	}
	ofPopStyle();
}

//-------------------------------------
void DSphareParticle::start()
{
	_isStart = true;
	generateParticle();
	computeTri();
}

//-------------------------------------
void DSphareParticle::stop()
{
	_isStart = false;
}

//-------------------------------------
void DSphareParticle::trigger()
{
	for (auto& iter : _particleList)
	{
		iter.setAmt(ofMap(ofNoise(iter._pos), 0, 1.0, 0.5, 1.8));
	}
}

//-------------------------------------
void DSphareParticle::setBaseSize(float size)
{
	_baseSize = size;
}

//-------------------------------------
void DSphareParticle::generateParticle()
{
	ofSeedRandom();

	for (int i = 0; i < cDPNumber; i++)
	{
		float theta_ = ofRandom(cDPThetaMin, cDPThetaMax);
		float thetaMin = MAX(theta_ - ofRandom(cDPThetaMoveMin, cDPThetaMoveMax), 0);
		float thetaMax = MIN(theta_ + ofRandom(cDPThetaMoveMin, cDPThetaMoveMax), PI);
		_particleList[i].set(
			theta_
			,ofRandom(TWO_PI)
			,(rand() % 2)?ofRandom(cDPSpeedMin, cDPSpeedMax): -ofRandom(cDPSpeedMin, cDPSpeedMax)
			,(rand() % 2)?ofRandom(cDPSpeedMin, cDPSpeedMax) : -ofRandom(cDPSpeedMin, cDPSpeedMax)
			, thetaMax
			, thetaMin
		);
		_tri.addVertex(_particleList[i]._pos);
	}
}

//-------------------------------------
void DSphareParticle::computeTri()
{
	ZeroMemory(_triCheck, sizeof(bool) * cDPNumber);
	_tri.clearIndices();
	for (int i = 0; i < cDPNumber; i++)
	{
		if (_triCheck[i])
		{
			continue;
		}

		int count = 0;
		int id[2] = { -1, -1 };
		for (int j = 0; j < cDPNumber; j++)
		{
			if (count == 2)
			{
				_triCheck[i] = true;
				_triCheck[id[0]] = true;
				_triCheck[id[1]] = true;
				_tri.addTriangle(i, id[0], id[1]);
				break;
			}

			if (_triCheck[j] || i == j)
			{
				continue;
			}

			auto dist_ = _particleList[i]._pos.distance(_particleList[j]._pos);
			if (dist_ < cDPNearLimit * _baseSize)
			{
				id[count] = j;
				count++;
			}
		}
	}
}
