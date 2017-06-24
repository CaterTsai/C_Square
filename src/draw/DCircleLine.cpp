#include "DCircleLine.h"

//-------------------------------------
void DCircleLine::update(float delta)
{
	CHECK_START();

	for (auto& iter : _cList)
	{
		iter.update(delta);
	}
}

//-------------------------------------
void DCircleLine::draw(int x, int y, int w, int h)
{
	CHECK_START();

	int baseR = MIN(w, h) * 0.8 * 0.5;

	ofPushStyle();
	ofSetColor(255);
	ofNoFill();
	{
		ofPushMatrix();
		ofTranslate(w / 2, h / 2);
		{
			drawCircle(0, baseR);
		}
		ofPopMatrix();
	}
	ofPopStyle();
}

//-------------------------------------
void DCircleLine::start()
{
	_isStart = true;
	initCircle();
}

//-------------------------------------
void DCircleLine::stop()
{
	_isStart = false;
}

//-------------------------------------
void DCircleLine::initCircle()
{
	_cList.clear();
	float size = 1.0;
	_cList.push_back(circle(size, PI * 0.5));
	for (int i = 0; i < 2; i++)
	{
		size *= ofRandom(0.2, 0.8);
		circle newCircle(size);
		newCircle.setFromParent(_cList[i]._r, _cList[i]._v);
		_cList.push_back(newCircle);
	}
}

//-------------------------------------
void DCircleLine::drawCircle(int cIdx, float baseR)
{
	
	if (cIdx >= _cList.size())
	{
		ofPushStyle();
		ofFill();
		ofSetColor(255, 0, 0);
		ofDrawCircle(0, 0, 2);
		ofPopStyle();
		return;
	}
	else
	{
		ofPushMatrix();

		if (cIdx != 0)
		{
			ofTranslate(0, (_cList[cIdx - 1]._r - _cList[cIdx]._r) * -baseR);
		}
		ofRotateZ(_cList[cIdx]._radin * RAD_TO_DEG);

		drawCircle(cIdx + 1, baseR);
		//ofDrawCircle(0, 0, _cList[cIdx]._r * baseR);
		//ofDrawLine(0, 0, 0, _cList[cIdx]._r * baseR * -1);
		ofPopMatrix();
	}
}
