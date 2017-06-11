#pragma once

#include "DBase.h"

class DFlash : public DBase
{
public:
	DFlash()
		:DBase(eDFlash)
		,_flashT(1.0)
		,_timer(0.0)
		,_flash(false)
		,_flashColor(255)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

	void setValue(DParam& value) override;

private:
	float _timer, _flashT;
	bool _flash;
	ofColor _flashColor;
};