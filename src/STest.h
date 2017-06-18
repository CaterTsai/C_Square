#pragma once

#include "SBase.h"
#include "glitchFilter.h"

class STest : public SBase
{
public:
	STest()
		:SBase(eSTest)
	{
	}

	void update(float delta) override;
	void draw() override;
	void start() override;
	void stop() override;

private:
	ofRectangle _drawRect;
	DLife _life;
	DECA _eca;

	glitchFilter _glitch;
};