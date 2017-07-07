#include "DPingPong.h"

#pragma region Ping-Pong Element
//-----------------------------------------
//Ball
DPingPong::ball::ball()
	:_pos(0)
	,_vec(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5))
	, _isDead(false)
{
}

//-----------------------------------------
void DPingPong::ball::update(float delta)
{
	_pos += _vec * delta;

	if (_pos.x < -0.5 || _pos.x > 0.5 || _pos.y < -0.5 || _pos.y > 0.5)
	{
		_isDead = true;
	}
}

//-----------------------------------------
//Bet
DPingPong::bet::bet(eBetType type, float length)
	:_type(type)
	, _length(length)
{
	switch (type)
	{
		case eBetTop:
		{
			_pos.set(0.0, -0.5);
			_s.set(-0.5, -0.5);
			_e.set(0.5, -0.5);
			break;
		}
		case eBetLeft:
		{
			_pos.set(-0.5, 0.0);
			_s.set(-0.5, 0.5);
			_e.set(-0.5, -0.5);
			break;
		}
		case eBetDown:
		{
			_pos.set(0.0, 0.5);
			_s.set(0.5, 0.5);
			_e.set(-0.5, 0.5);
			break;
		}
		case eBetRight:
		{
			_pos.set(0.5, 0.0);
			_s.set(0.5, -0.5);
			_e.set(0.5, 0.5);
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
		ofVec2f _vec = targetPos - _pos;
		_vec.limited(0.5);
	}

	//Update Pos
	_pos += _vec * delta;
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
			float dist = -0.5 - b._pos.y;
			t = abs(dist / b._vec.y);
			break;
		}
		}
	}
	pos += b._vec * t;

	return result;
}
#pragma endregion

//-----------------------------------------
void DPingPong::update(float delta)
{
}

//-----------------------------------------
void DPingPong::draw(int x, int y, int w, int h)
{
}

//-----------------------------------------
void DPingPong::start()
{
}

//-----------------------------------------
void DPingPong::stop()
{
}
