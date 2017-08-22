#pragma once

#include "DBase.h"

class DAudioRect : public DBase
{
public:
	DAudioRect()
		:DBase(eDAudioRect)
		, _isHorizon(true)
		, _rectColor(255)
	{
	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

	void setSoundValue(array<float, cBufferSize>& soundValue);

	inline void toggleHorizon()
	{
		_isHorizon ^= true;
	}
	inline void setHorizon(bool val)
	{
		_isHorizon = val;
	}
	inline void setColor(ofColor c)
	{
		_rectColor = c;
	}
private:

private:
	bool _isHorizon;
	ofColor _rectColor;
	array<bool, cDAudioRectNum> _needToDraw;
};