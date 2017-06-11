#pragma once

#include "SBase.h"

class STest : public SBase
{
public:
	STest()
		:SBase(eSTest)
	{}

	void update(float delta) override;
	void draw() override;
	void start() override;
	void stop() override;

private:
};