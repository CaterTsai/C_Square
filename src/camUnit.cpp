#include "camUnit.h"

//--------------------------------------------------------------
camUnit::camUnit()
	:_type(eCamFixed)
	, _playType(eMoveRepeat)
	, _target(0)
{	
	//_cam.disableMouseInput();
	//_cam.setAutoDistance(false);
}

//--------------------------------------------------------------
void camUnit::update(float delta)
{
	bool needLookup = true;
	switch (_type)
	{
		case eCamRotate:
		case eCamRotateBetween:
		{
			updateRotate(delta);
			needLookup = false;
			break;
		}
		case eCamRevolution:
		case eCamRevolutionBetween:
		{
			updateRevolution(delta);
			break;
		}
		case eCamMoveBetween:
		{
			updateMove(delta);
			break;
		}
		case eCamRandomOnBall:
		{
			updateRandom(delta);
			break;
		}
	}

	if (needLookup)
	{
		_cam.lookAt(_target);
	}
	
}

//--------------------------------------------------------------
void camUnit::drawCam()
{
	ofPushStyle();
	ofNoFill();
	ofSetColor(255, 0, 0);
	ofDrawSphere(100);
	ofFill();
	ofSetColor(255);
	_cam.draw();
	ofPopStyle();
}

//--------------------------------------------------------------
void camUnit::setPlayType(eCamMovePlayType type)
{
	_playType = type;
}

//--------------------------------------------------------------
void camUnit::stop()
{
	setFixed();
}

//--------------------------------------------------------------
void camUnit::setFixed()
{
	_type = eCamFixed;
}

//--------------------------------------------------------------
void camUnit::setFixed(ofVec3f& pos)
{
	_type = eCamFixed;
	_cam.setGlobalPosition(pos);
	_cam.lookAt(_target);
}

//--------------------------------------------------------------
void camUnit::setRotate(float vec)
{
	_type = eCamRotate;
	_rVec = vec;

}

//--------------------------------------------------------------
void camUnit::setRotate(float from, float to, float t)
{
	_type = eCamRotateBetween;
	_rAngle = _rFrom = from;
	_rTo = to;
	setPorc(t);

}

//--------------------------------------------------------------
void camUnit::setRevolution(ofVec3f& axis, float vec)
{
	_type = eCamRevolution;
	_revAxis = axis;
	_revV = vec;
}

//--------------------------------------------------------------
void camUnit::setRevolution(ofVec3f& axis, float from, float to, float t)
{
	_type = eCamRevolutionBetween;
	_revAxis = axis;
	_revAngle = _revFrom = from;
	_revTo = to;
	setPorc(t);
}

//--------------------------------------------------------------
void camUnit::setMove(ofVec3f & to, float t)
{
	setMove(_cam.getGlobalPosition(), to, t);
}

//--------------------------------------------------------------
void camUnit::setMove(ofVec3f& from, ofVec3f& to, float t)
{
	_type = eCamMoveBetween;
	_posFrom = from;
	_posTo = to;
	setPorc(t);

}

//--------------------------------------------------------------
void camUnit::setRandom(int dist, float t)
{
	_type = eCamRandomOnBall;
	_dist = dist;
	_timer = _randTime = t;

	ofVec3f randPos(dist, ofRandom(0, PI), ofRandom(0, TWO_PI));
	_cam.setGlobalPosition(randPos);
}

//--------------------------------------------------------------
void camUnit::setTarget(ofVec3f& pos)
{
	_target = pos;
}

//--------------------------------------------------------------
void camUnit::updateRotate(float delta)
{
	if (_type == eCamRotate)
	{
		float angle = _rVec * delta;
		_cam.roll(RAD_TO_DEG * angle);
	}
	else
	{
		updatePrec(delta);
		float angle = _rFrom * (1.0 - _prec) + _rTo * _prec;
		float diff = angle - _rAngle;
		_rAngle = angle;
		_cam.roll(RAD_TO_DEG * diff);
	}
}

//--------------------------------------------------------------
void camUnit::updateRevolution(float delta)
{
	if (_type == eCamRevolution)
	{
		float angle = _revV * delta;
		_cam.rotateAround(RAD_TO_DEG * angle, _revAxis, _target);
	}
	else
	{
		updatePrec(delta);
		float angle = _revFrom * (1.0 - _prec) + _revTo * _prec;
		float diff = angle - _revAngle;
		_revAngle = angle;
		_cam.rotateAround(RAD_TO_DEG * diff, _revAxis, _target);
	}
}

//--------------------------------------------------------------
void camUnit::updateMove(float delta)
{
	updatePrec(delta);
	ofVec3f pos = _posFrom.getInterpolated(_posTo, _prec);
	_cam.setGlobalPosition(pos);
}

//--------------------------------------------------------------
void camUnit::updateRandom(float delta)
{
	_timer -= delta;
	if (_timer <= .0)
	{
		_timer = _randTime;
		ofVec3f randPos(_dist, ofRandom(0, PI), ofRandom(0, TWO_PI));
		_cam.setGlobalPosition(Spherical2Cartesian(randPos));
	}
}

//--------------------------------------------------------------
void camUnit::setPorc(float t)
{
	_prec = 0.0;
	_v = 1.0 / t;
}

//--------------------------------------------------------------
void camUnit::updatePrec(float delta)
{
	_prec += _v * delta;
	if (_prec >= 1.0)
	{
		switch (_playType)
		{
			case eMoveOnce:
			{
				_prec = 1.0;
				_v = 0;
				break;
			}
			case eMoveRepeat:
			{
				_prec = 0.0;
				break;
			}
			case eMoveRepeatBack:
			{
				_prec = 1.0;
				_v = -_v;
				break;
			}
		}
	}
	
	if (_prec < 0.0 && _playType == eMoveRepeatBack)
	{
		_prec = 0.0;
		_v = -_v;
	}
}

//--------------------------------------------------------------
ofVec3f camUnit::Spherical2Cartesian(ofVec3f pos)
{
	ofVec3f r;
	r.x = pos.x * sin(pos.y) * cos(pos.z);
	r.y = pos.x * sin(pos.y) * sin(pos.z);
	r.z = pos.x * cos(pos.y);
	
	return r;
}

//--------------------------------------------------------------
ofVec3f camUnit::Cartesian2Spherical(ofVec3f pos)
{
	ofVec3f r;
	r.x = pos.distance(ofVec3f(0));
	r.y = r.x > 0 ? (pos.z / r.x) : 0;
	r.z = r.x > 0 ? (pos.y, pos.x) : 0;
	return r;
}
