#pragma once

#include "SBase.h"
#include "glitchFilter.h"

class STest : public SBase
{
public:
	STest()
		:SBase(eSTest)
		,_autoRotate(true)
	{
	}

	void update(float delta) override;
	void draw() override;
	void start() override;
	void stop() override;

	void trigger();

private:
	ofRectangle _drawRect;
	DLife _life;
	DECA _eca;
	DCircleLine _cl;
	DSphareParticle _dp;
	DCylinderFlow _cf;

	glitchFilter _glitch;
	bool _enableGlitch;

	bool _autoRotate;
	ofEasyCam	_cam;
};