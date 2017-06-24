#pragma once

#include "DBase.h"

class DCircleLine : public DBase
{
#pragma region Circle
private:
	class circle
	{
	public:
		circle(float r = 0, float v = 0)
			:_r(r)
			,_radin(0)
			,_v(v)
		{}
		
		void setRadio(float r)
		{
			_r = r;
		}
		void setFromParent(float pr, float pv)
		{
			//auto distP = ps * pv;// <- (ps * 2 * PI) * (pv / (2 * PI));
			//_v = distP / s;//(distP / <- (s * 2 * PI)) * 2 * PI;
			_v = (pr * pv) / _r;
		}

		void update(float delta)
		{
			_radin += delta * _v;
			if (_radin > 2 * PI)
			{
				_radin -= 2 * PI;
			}
		}

	public:
		float _r;
		float _radin, _v;
	};
#pragma endregion
	
public:
	DCircleLine()
		:DBase(eDCircleLine)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void initCircle();
	void drawCircle(int cIdx, float baseR);

private:
	vector<circle> _cList;
	list<ofVec2f> _pList;
};