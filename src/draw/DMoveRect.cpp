#include "DMoveRect.h"

//----------------------------------
void DMoveRect::update(float delta)
{
	CHECK_START();
	_animMove.update(delta);

	if (_animMove.hasFinishedAnimating() && _animMove.getPercentDone() == 1.0)
	{
		_nowID = _enterID;
		_nowColor = _enterColor;
	}
}

//----------------------------------
void DMoveRect::draw(int id, int x, int y, int w, int h)
{
	CHECK_START();

	if (id != _nowID && id != _enterID && id != _exitID)
	{
		return;
	}

	if (_animMove.isAnimating())
	{
		bool isEnter = (id == _enterID);
		ofPushStyle();
		ofFill();
		ofSetColor(isEnter ? _enterColor : _exitColor);
		auto center = getMoveCenter(isEnter);
		ofDrawRectangle(w * (center.x - 0.5), h * (center.y - 0.5), w, h);
		
		ofPopStyle();
	}
	else
	{
		if (id == _nowID)
		{
			ofPushStyle();
			ofFill();
			ofSetColor(_nowColor);
			ofDrawRectangle(w * -0.5, h * -0.5, w, h);
			ofPopStyle();
		}
	}
}

//----------------------------------
void DMoveRect::start()
{
	_isStart = true;
	
	_animMove.setDuration(0.5);
	_animMove.setCurve(AnimCurve::EASE_IN_BACK);
	//_animMove.setRepeatType(AnimRepeat::PLAY_ONCE);

	_nowID = _enterID = _exitID = -1;
	ofColor red(255, 0, 0);
	_enterColor = red;
	_enterColor.setHueAngle(rand() % 360);
	move(rand() % _groupNum);
}

//----------------------------------
void DMoveRect::stop()
{
	_isStart = false;
}

//----------------------------------
void DMoveRect::trigger()
{
	move( (_nowID + 1) % _groupNum);
}

//----------------------------------
void DMoveRect::setGroupNum(int num)
{
	_groupNum = num;
}

//----------------------------------
void DMoveRect::move(int target)
{
	if (_animMove.isAnimating())
	{
		_animMove.pause();
		_nowID = _enterID;
		_nowColor = _enterColor;
	}
	_animMove.animateFromTo(0.0, 1.0);
	_enterID = target;
	_exitID = _nowID;
	_exitColor = _nowColor;
	int direction = (rand() % 4);
	_eEnterD = (eEnterDirection)direction;
	_eExitD = (eExitDirection)direction;

	auto h = _enterColor.getHueAngle();
	_enterColor.setHueAngle(h + rand() % 60 + 30);
}

//----------------------------------
ofVec2f DMoveRect::getMoveCenter(bool isEnter)
{
	ofVec2f center(0, 0);
	float p = _animMove.getCurrentValue();
	if (isEnter)
	{
		switch (_eEnterD)
		{
			case eEnterUp:
			{
				center.set(0, -1);
				center.y += p;
				break;
			}
			case eEnterDown:
			{
				center.set(0, 1);
				center.y += -p;
				break;
			}
			case eEnterLeft:
			{
				center.set(-1, 0);
				center.x += p;
				break;
			}
			case eEnterRight:
			{
				center.set(1, 0);
				center.x += -p;
				break;
			}
		}
	}
	else
	{
		switch (_eExitD)
		{
		case eExitDown:
		{
			center.y += p;
			break;
		}
		case eExitUp:
		{
			center.y += -p;
			break;
		}
		case eExitRight:
		{
			center.x += p;
			break;
		}
		case eExitLeft:
		{
			center.x += -p;
			break;
		}
		}
	}

	return center;
}
