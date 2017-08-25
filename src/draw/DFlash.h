#pragma once

#include "DBase.h"

class DFlash : public DBase
{
public:
	DFlash()
		:DBase(eDFlash)
		,_flashT(1.0)
		,_flash(false)
		, _autoFlash(false)
		,_flashColor(255)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;
	void trigger() override;
	void setAutoFlash(bool val, float time = 0.0);

private:
	float _flashT;
	bool _flash, _autoFlash;
	ofColor _flashColor;
};