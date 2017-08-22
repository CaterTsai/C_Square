#include "DAudioRect.h"

//----------------------------------------------
void DAudioRect::update(float delta)
{
	CHECK_START();
}

//----------------------------------------------
void DAudioRect::draw(int x, int y, int w, int h)
{
	CHECK_START();

	float width, height;
	ofVec2f move;
	if (_isHorizon)
	{
		width = w;
		height = static_cast<int>(h / cDAudioRectNum);
		move.set(0, height);
	}
	else
	{
		width = static_cast<int>(w / cDAudioRectNum);
		height = h;
		move.set(width, 0);
	}
	ofRectangle rect(w * -0.5, h * -0.5, width, height);
	ofPushStyle();
	ofSetColor(_rectColor);
	{
		for (int i = 0; i < cDAudioRectNum; i++)
		{
			if (_needToDraw[i])
			{
				ofDrawRectangle(rect);
			}

			rect.x += move.x;
			rect.y += move.y;
		}
	}
	ofPopStyle();
}

//----------------------------------------------
void DAudioRect::start()
{
	_isStart = true;
	fill(_needToDraw.begin(), _needToDraw.end(), false);
}

//----------------------------------------------
void DAudioRect::stop()
{
	_isStart = false;
}

//----------------------------------------------
void DAudioRect::setSoundValue(array<float, cBufferSize>& soundValue)
{
	for (int i = 0; i < _needToDraw.size(); i++)
	{
		float count = .0f;
		for (int j = 0; j < cDAudioRectCheckSize; j++)
		{
			count += abs(soundValue[i * cDAudioRectCheckSize + j]);
		}
		count /= (float)cDAudioRectCheckSize;
		_needToDraw[i] = (count > cDAudioRectThreshold);
	}
}
