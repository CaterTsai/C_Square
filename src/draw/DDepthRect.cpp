#include "DDepthRect.h"

#pragma region Depth Rect
//-------------------------------------
void DDepthRect::depthRect::update(float delta)
{
	_animDepth.update(delta);
	_animRotate.update(delta);
}

//-------------------------------------
bool DDepthRect::depthRect::isDepthAnimFinish()
{
	return (_animDepth.hasFinishedAnimating() && _animDepth.getPercentDone() == 1.0);
}

//-------------------------------------
void DDepthRect::depthRect::moveTo(float t, float depth)
{
	if (_animDepth.isOrWillBeAnimating())
	{
		_animDepth.pause();
	}

	_animDepth.setDuration(t);
	_animDepth.animateTo(depth);
}

//-------------------------------------
void DDepthRect::depthRect::moveToDelay(float t, float depth, float delay)
{
	if (_animDepth.isOrWillBeAnimating())
	{
		_animDepth.pause();
	}

	_animDepth.setDuration(t);
	_animDepth.animateToAfterDelay(depth, delay);
}

//-------------------------------------
void DDepthRect::depthRect::rotateTo(float t, float radin)
{
	if (_animRotate.isOrWillBeAnimating())
	{
		_animRotate.pause();
	}

	_animRotate.setDuration(t);
	_animRotate.animateTo(radin);
}

//-------------------------------------
void DDepthRect::depthRect::rotateToDelay(float t, float radin, float delay)
{
	if (_animRotate.isOrWillBeAnimating())
	{
		_animRotate.pause();
	}


	_animRotate.setDuration(t);
	_animRotate.animateToAfterDelay(radin, delay);
}
#pragma endregion

//-------------------------------------
void DDepthRect::update(float delta)
{
	CHECK_START();

	for (auto& iter : _depthList)
	{
		iter.update(delta);
	}
	animCheck();
	colorUpdate(delta);
}

//-------------------------------------
void DDepthRect::draw(int x, int y, int w, int h)
{
	CHECK_START();
	
	int size = w;
	int halfSize = w * 0.5;

	ofPushStyle();
	ofNoFill();
	for (int i = 0; i < _depthList.size(); i++)
	{
		if (_depthList[i]._display)
		{
			if (i == _colorIdx)
			{
				ofSetLineWidth(8);
				ofSetColor(33, 255, 54);
			}
			else
			{
				ofSetLineWidth(5);
				ofSetColor(255);
			}

			
			float z = _depthList[i]._animDepth.getCurrentValue() * h * -5.0;
			ofPushMatrix();
			ofTranslate(0, 0, z);
			ofRotateZ(_depthList[i]._animRotate.getCurrentValue() * RAD_TO_DEG);
			{
				ofDrawRectangle(-halfSize, -halfSize, 0, size, size);
			}
			ofPopMatrix();
		}
		size *= 0.9;
		halfSize = size * 0.5;
	}
	
	ofPopStyle();
}

//-------------------------------------
void DDepthRect::start()
{
	_isStart = true;
	_depthMoveT = 0.1;
	_colorChangeT = 0.05;
	_eState = eIdle;
	initDepthList();
	_colorIdx = -1;
	enter();
}

//-------------------------------------
void DDepthRect::stop()
{
	_isStart = false;
}

//-------------------------------------
void DDepthRect::trigger()
{
	rotate();
}

//-------------------------------------
void DDepthRect::initDepthList()
{
	_depthList.clear();

	for (int i = 0; i < cDDepthRectNum; i++)
	{
		_depthList.push_back(depthRect());
	}

}

//-------------------------------------
void DDepthRect::animCheck()
{
	switch (_eState)
	{
	case eEnter:
	{
		if (_depthList[_rectAnimIdx].isDepthAnimFinish())
		{
			_rectAnimIdx++;
			if (_rectAnimIdx == cDDepthRectNum)
			{
				_timer = _colorChangeT;
				_colorIdx = 0;
				_eState = ePlay;
			}
			else
			{
				_depthList[_rectAnimIdx]._display = true;
				_depthList[_rectAnimIdx]._animDepth.reset((_rectAnimIdx - 1) * 1.0f / cDDepthRectNum);
				_depthList[_rectAnimIdx].moveTo(_depthMoveT, _rectAnimIdx * 1.0f / cDDepthRectNum);
			}
		}
		break;
	}
	case eExit:
	{
		if (_depthList[_rectAnimIdx].isDepthAnimFinish())
		{
			_depthList[_rectAnimIdx]._display = false;
			_rectAnimIdx--;
			if (_rectAnimIdx == 0)
			{
				_depthList[_rectAnimIdx]._display = false;
				_eState = eIdle;
			}
			else
			{
				_depthList[_rectAnimIdx].moveTo(_depthMoveT, (_rectAnimIdx - 1) * 1.0f / cDDepthRectNum);
			}
		}
		break;
	}
	}
}

//-------------------------------------
void DDepthRect::enter()
{
	_eState = eEnter;
	_rectAnimIdx = 1;
	_depthList[0]._display = true;
	_depthList[0]._animDepth.reset(0);

	_depthList[1]._display = true;
	_depthList[1]._animDepth.reset(0);
	_depthList[1].moveTo(_depthMoveT, 1.0f/ cDDepthRectNum);
}

//-------------------------------------
void DDepthRect::exit()
{
	_eState = eExit;
	_rectAnimIdx = cDDepthRectNum - 1;
	_depthList[_rectAnimIdx].moveTo(_depthMoveT, _rectAnimIdx * 1.0f / cDDepthRectNum);
}

//-------------------------------------
void DDepthRect::rotate()
{
	if (_eState == ePlay)
	{
		float animT = 0.1;
		float delayT = 0.0;
		float radin = _depthList[0]._animRotate.getCurrentValue() + ofRandom(cDDRotateMin, cDDRotateMax);
		float diff = ofRandom(cDDRotateDiffMin, cDDRotateDiffMin);
		for (auto& iter : _depthList)
		{
			iter.rotateToDelay(animT, radin, delayT);
			delayT += animT * 0.5;
			radin += diff;
		}
	}
}

//-------------------------------------
void DDepthRect::rotateReset()
{
	if (_eState == ePlay)
	{
		float animT = 0.2;
		float delayT = 0.0;
		for (auto& iter : _depthList)
		{
			iter.rotateToDelay(animT, 0, delayT);
			delayT += animT * 0.5;
		}
	}
}

//-------------------------------------
void DDepthRect::colorUpdate(float delta)
{
	if (_eState == ePlay)
	{
		_timer -= delta;
		if (_timer <= 0.0f)
		{
			_timer = 0.5 * 60.0 / globalVariable::gBPM;
			_colorIdx = (_colorIdx + 1) % cDDepthRectNum;
		}
	}
}
