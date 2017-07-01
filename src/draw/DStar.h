#pragma once

#include "DBase.h"

class DStar : public DBase
{
private:
	struct star
	{
		star(bool forward)
			:pos(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0))
			,v(ofRandom(cDStarMinV, cDStarMaxV))
		{
			if (forward)
			{
				v = -v;
			}
			else
			{
				pos.z = -cDStarMoveMax;
			}
		}
		ofVec3f pos;
		float v;
	};

public:
	DStar()
		:DBase(eDStar)
		, _forward(false)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void updateStar(float delta);
	void addStar(int num);
private:
	bool _forward;
	list<star>	_starList;
};