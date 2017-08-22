#pragma once

#include "DBase.h"

class DAudioRect : public DBase
{
public:
	DAudioRect()
		:DBase(eDAudioRect)
	{

	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

	void setSoundValue(array<float, cBufferSize>& soundValue);


private:

private:
	bool _isHorizon;
	ofColor _rectColor;
	vector<bool> _needToDraw;
};