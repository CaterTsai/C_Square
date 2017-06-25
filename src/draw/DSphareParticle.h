#pragma once

#include "DBase.h"

class DSphareParticle : public DBase
{

#pragma region particle
	class particle
	{
	public:
		particle()
			:_t(0.0)
			,_p(0.0)
			,_amt(1.0)
			,_vt(0.0)
			,_vp(0.0)
			,_nearId(-1)
		{};

		particle(float t, float p, float vt, float vp)
			:_t(t)
			,_p(p)
			,_amt(1.0)
			, _vt(vt)
			, _vp(vp)
			, _nearId(-1)
		{}

		void set(float t, float p, float vt, float vp);
		void update(float delta);

		inline bool haveNear()
		{
			return _nearId != -1;
		}

		inline void resetNear()
		{
			_nearId = -1;
		}
		
	public:
		float _t, _p;
		float _amt;
		float _vt, _vp;
		ofVec3f _pos;
		int _nearId;
	};
#pragma endregion


public:
	DSphareParticle()
		:DBase(eDSphereParticle)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void generateParticle();

	void drawNear(int size);
	void computeNear();
private:
	ofEasyCam _cam;
	array<DSphareParticle::particle, cDPNumber> _particleList;
};