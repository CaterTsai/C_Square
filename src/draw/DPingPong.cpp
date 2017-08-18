#include "DPingPong.h"

#pragma region Ping-Pong Element

#pragma region Ball
//-----------------------------------------
//Ball
DPingPong::ball::ball()
	:_pos(0)
	,_vec(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5))
	,_r(ofRandom(0.02, 0.05))
	,_isDead(false)
	,_isCross(false)
{
	_color.set(255, 100, 100);
	_color.setHueAngle(ofRandom(0, 360));
}

//-----------------------------------------
void DPingPong::ball::update(float delta, vector<bet>& betList)
{
	if (_isDead)
	{
		return;
	}

	for (auto& iter : betList)
	{
		iter.checkTouch(this);
	}

	auto nextPos = _pos + _vec * delta;
	if ((nextPos.y > 0.0 && _pos.y < 0.0) || (nextPos.y < 0.0 && _pos.y > 0.0))
	{
		_isCross = true;
	}
	_pos = nextPos;

	if (_pos.x < -0.5 || _pos.x > 0.5 || _pos.y < -0.5 || _pos.y > 0.5)
	{
		_isDead = true;
	}
}
#pragma endregion

#pragma region Bet
//-----------------------------------------
//Bet
DPingPong::bet::bet(eBetType type, float length)
	:_type(type)
	, _length(length)
	, _halfL(length * 0.5)
{
	switch (type)
	{
	case eBetTop:
	{
		_pos.set(0.0, -0.5);
		_s.set(-0.5 + _halfL, -0.5);
		_e.set(0.5 - _halfL, -0.5);
		break;
	}
	case eBetLeft:
	{
		_pos.set(-0.5, 0.0);
		_s.set(-0.5, 0.5 - _halfL);
		_e.set(-0.5, -0.5 + _halfL);
		break;
	}
	case eBetDown:
	{
		_pos.set(0.0, 0.5);
		_s.set(0.5 - _halfL, 0.5);
		_e.set(-0.5 + _halfL, 0.5);
		break;
	}
	case eBetRight:
	{
		_pos.set(0.5, 0.0);
		_s.set(0.5, -0.5 + _halfL);
		_e.set(0.5, 0.5 - _halfL);
		break;
	}
	}
}

//-----------------------------------------
void DPingPong::bet::update(float delta, list<ball>& ballList)
{
	//Update Vec
	bool needUpdate = false;
	float t = numeric_limits<float>::max();
	ofVec2f targetPos(0);
	for (auto& iter : ballList)
	{
		ofVec2f nextPos;
		float nextT = 0.0f;
		if (getTouchPosAndTime(iter, nextPos, nextT))
		{
			if (t > nextT)
			{
				t = nextT;
				targetPos.set(nextPos);
				needUpdate = true;
			}
		}
	}

	if (needUpdate)
	{
		_vec = (targetPos - _pos) / t;
		//_vec.limit(1.0);
	}

	//Update Pos
	_pos += _vec * delta;
	limitCheck();
}

//-----------------------------------------
void DPingPong::bet::draw(float width, float height)
{
	ofPushStyle();
	ofFill();
	switch (_type)
	{
	case eBetTop:
	{
		ofDrawRectangle((_pos.x - _halfL) * width, _pos.y * width, _length * width, 0.2 * _halfL * width);
		break;
	}
	case eBetDown:
	{
		ofDrawRectangle((_pos.x - _halfL) * width, (_pos.y - 0.2 * _halfL) * width, _length * width, 0.2 * _halfL * width);
		break;
	}
	case eBetLeft:
	{
		ofDrawRectangle(_pos.x * width, (_pos.y - _halfL) * width, 0.2 * _halfL * width, _length * width);
		break;
	}
	case eBetRight:
	{
		ofDrawRectangle((_pos.x - 0.2 * _halfL)* width, (_pos.y - _halfL) * width, 0.2 * _halfL * width, _length * width);
		break;
	}
	}

	ofPopStyle();
}

//-----------------------------------------
void DPingPong::bet::checkTouch(ball* b)
{
	switch (_type)
	{
	case eBetTop:
	{
		if (abs(b->_pos.y - _pos.y) <= b->_r && abs(b->_pos.x - _pos.x) <= _halfL && b->_vec.y < 0.0)
		{
			b->_vec.y = -b->_vec.y;
			b->_pos.y = _pos.y + b->_r;
		}
		break;
	}
	case eBetDown:
	{
		if (abs(b->_pos.y - _pos.y) <= b->_r && abs(b->_pos.x - _pos.x) <= _halfL && b->_vec.y >0.0)
		{
			b->_vec.y = -b->_vec.y;
			b->_pos.y = _pos.y - b->_r;
		}
		break;
	}
	case eBetLeft:
	{
		if (abs(b->_pos.x - _pos.x) <= b->_r && abs(b->_pos.y - _pos.y) <= _halfL && b->_vec.x < 0.0)
		{
			b->_vec.x = -b->_vec.x;
			b->_pos.x = _pos.x + b->_r;
		}
		break;
	}
	case eBetRight:
	{
		if (abs(b->_pos.x - _pos.x) <= b->_r && abs(b->_pos.y - _pos.y) <= _halfL && b->_vec.x > 0.0)
		{
			b->_vec.x = -b->_vec.x;
			b->_pos.x = _pos.x - b->_r;
		}
		break;
	}
	}
}

//-----------------------------------------
bool DPingPong::bet::getTouchPosAndTime(ball b, ofVec2f & pos, float & t)
{
	bool result = false;
	pos = b._pos;
	switch (_type)
	{
	case eBetTop:
	{
		result = (b._vec.y < 0.0);
		break;
	}
	case eBetLeft:
	{
		result = (b._vec.x < 0.0);
		break;
	}
	case eBetDown:
	{
		result = (b._vec.y > 0.0);
		break;
	}
	case eBetRight:
	{
		result = (b._vec.x > 0.0);
		break;
	}
	}

	if (result)
	{
		switch (_type)
		{
		case eBetTop:
		{
			float dist = -0.5 - b._pos.y;
			t = abs(dist / b._vec.y);
			break;
		}
		case eBetLeft:
		{
			float dist = -0.5 - b._pos.x;
			t = abs(dist / b._vec.x);
			break;
		}
		case eBetDown:
		{
			float dist = 0.5 - b._pos.y;
			t = abs(dist / b._vec.y);
			break;
		}
		case eBetRight:
		{
			float dist = 0.5 - b._pos.x;
			t = abs(dist / b._vec.x);
			break;
		}
		}
	}
	pos = b._pos + b._vec * t;

	return result;
}

//-----------------------------------------
void DPingPong::bet::limitCheck()
{
	switch (_type)
	{
	case eBetTop:
	{
		_pos.x = MIN(MAX(_pos.x, _s.x), _e.x);
		break;
	}
	case eBetLeft:
	{
		_pos.y = MIN(MAX(_pos.y, _e.y), _s.y);
		break;
	}
	case eBetDown:
	{
		_pos.x = MIN(MAX(_pos.x, _e.x), _s.x);
		break;
	}
	case eBetRight:
	{
		_pos.y = MIN(MAX(_pos.y, _s.y), _e.y);
		break;
	}
	}
}
#pragma endregion

#pragma region Ripple
//-----------------------------------------
//Ripple
DPingPong::ripple::ripple(ofVec2f pos, ofColor c)
	:_isDead(false)
	,_pos(pos)
	, _c(c)
	,_r(0.0)
	,_rv(1.5)
{
}

//-----------------------------------------
void DPingPong::ripple::update(float delta)
{
	if (_isDead)
	{
		return;
	}

	_r += _rv * delta;

	if (_r > 1.0)
	{
		_isDead = true;
	}
}

//-----------------------------------------
void DPingPong::ripple::draw(float w)
{
	ofPushStyle();
	ofSetColor(_c);
	ofNoFill();
	ofSetLineWidth(w * 0.02);
	{
		ofDrawCircle(_pos * w, _r * w);
	}
	ofPopStyle();
}
#pragma endregion

#pragma region Wire
//-----------------------------------------
//Wire
DPingPong::wire::wire()
	:_s(0)
	,_e(0)
	, _moveV(0)
{
	reset();
}

//-----------------------------------------
void DPingPong::wire::update(float delta)
{
	for (auto& iter : _wireNodes)
	{
		if (iter > 0.05 || iter < -0.05)
		{
			iter *= 0.9;
		}
		else
		{
			iter = 0;
		}
	}
}

//-----------------------------------------
void DPingPong::wire::draw(float size)
{
	ofPushStyle();

	ofSetColor(255);
	{
		ofPath path;
		path.setColor(ofColor(255));
		path.setStrokeWidth(1.0);
		//path.setFilled(false);
		
		path.moveTo(_s * size);
		ofVec2f inv = (_e - _s) / cDPPWireNode;	
		for (int i = 1; i < cDPPWireNode; i++)
		{
			ofVec2f node = (_s + inv * i) * size;
			node += _moveV * _wireNodes[i] * size * 0.5;
			path.curveTo(node);
		}
		path.lineTo(_e * size);
		//path.close();

		path.draw();
	}
	ofPopStyle();
}

//-----------------------------------------
void DPingPong::wire::reset()
{
	ZeroMemory(_wireNodes, sizeof(float) * cDPPWireNode);
}

//-----------------------------------------
void DPingPong::wire::set(ofVec2f start, ofVec2f end)
{
	_s = start;
	_e = end;
	_moveV = (_e - _s).getRotatedRad(PI * -0.5);
	_moveV.normalize();
}

//-----------------------------------------
void DPingPong::wire::addWave(ofVec2f p)
{
	int idx = static_cast<int>((_s.distance(p) / _s.distance(_e)) * cDPPWireNode + 0.5);
	_wireNodes[idx] = ofRandom(-1, 1);
	for (int i = 1; i < cDPPWireHodeHalf; i++)
	{
		
		float d = (1.0 - (float)i / cDPPWireHodeHalf);
		
		if (idx + i < cDPPWireNode - 1)
		{
			_wireNodes[idx + i] = ofRandom(-1, 1) * d;
		}

		if (idx - i > 0)
		{
			_wireNodes[idx - i] = ofRandom(-1, 1) * d;
		}
	}
}
#pragma endregion

#pragma endregion

//-----------------------------------------
void DPingPong::update(float delta)
{
	CHECK_START();

	//ball
	auto ballIter = _ballList.begin();
	while (ballIter != _ballList.end())
	{
		ballIter->update(delta, _bels);
		if (ballIter->_isDead)
		{
			ballIter = _ballList.erase(ballIter);
		}
		else
		{
			if (ballIter->_isCross)
			{
				addRipple(ballIter->_pos, ballIter->_color);
				_hWire.addWave(ballIter->_pos);
				ballIter->_isCross = false;
			}
			ballIter++;
		}
	}

	//ripple
	auto rippleIter = _rippleList.begin();
	while (rippleIter != _rippleList.end())
	{
		rippleIter->update(delta);
		if (rippleIter->_isDead)
		{
			rippleIter = _rippleList.erase(rippleIter);
		}
		else
		{
			rippleIter++;
		}
	}

	//bel
	for (auto& iter : _bels)
	{
		iter.update(delta, _ballList);
	}

	//wire
	_hWire.update(delta);
}

//-----------------------------------------
void DPingPong::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	ofDisableDepthTest();
	ofSetColor(255);
	{
		_hWire.draw(w);
		for (auto& iter : _rippleList)
		{
			iter.draw(w);
		}

		for (auto& iter : _bels)
		{
			iter.draw(w, h);
		}

		for (auto& iter : _ballList)
		{
			ofSetColor(iter._color);
			ofDrawCircle(iter._pos * w, iter._r * w);
		}
	}
	ofPopStyle();
}

//-----------------------------------------
void DPingPong::start()
{
	_isStart = true;
	
	_hWire.set(ofVec2f(-0.5, 0), ofVec2f(0.5, 0));
	_hWire.reset();
	initBoard();
}

//-----------------------------------------
void DPingPong::stop()
{
	_isStart = false;
}

//-----------------------------------------
void DPingPong::triggerBall()
{
	addBall(1);
}

//-----------------------------------------
void DPingPong::triggerRipple()
{

	ofColor c(255, 100, 100);
	c.setHueAngle(ofRandom(0, 360));
	addRipple(ofVec2f(0, 0), c);
}

//-----------------------------------------
void DPingPong::clearBall()
{
	_ballList.clear();
}

//-----------------------------------------
void DPingPong::initBoard()
{
	_bels.clear();
	_rippleList.clear();
	_ballList.clear();

	//Add ball

	_bels.push_back(bet(DPingPong::eBetType::eBetTop, 0.2));
	_bels.push_back(bet(DPingPong::eBetType::eBetLeft, 0.2));
	_bels.push_back(bet(DPingPong::eBetType::eBetDown, 0.2));
	_bels.push_back(bet(DPingPong::eBetType::eBetRight, 0.2));
}

//-----------------------------------------
void DPingPong::addBall(int num)
{
	for (int i = num; i > 0; i--)
	{
		_ballList.push_back(ball());
	}
}

//-----------------------------------------
void DPingPong::addRipple(ofVec2f & pos, ofColor & c)
{
	_rippleList.push_back(ripple(pos, c));
}

