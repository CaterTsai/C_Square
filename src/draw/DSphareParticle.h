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
			,_vt(0.0)
			,_vp(0.0)
			, _haveNear(false)
		{};

		particle(float t, float p, float vt, float vp)
			:_t(t)
			,_p(p)
			, _vt(vt)
			, _vp(vp)
			,_haveNear(false)
		{}

		void set(float t, float p, float vt, float vp);
		void update(float delta);

		inline bool haveNear()
		{
			return _haveNear;
		}

		inline void resetNear()
		{
			_haveNear = false;
		}

		inline ofVec3f getPos()
		{
			return _pos;
		}

		inline ofVec3f getNearPos()
		{
			return _near;
		}

		inline void setNearPos(ofVec3f n)
		{
			_near = n;
			_haveNear = true;
		}
		
	private:
		bool _haveNear;
		float _t, _p;
		float _vt, _vp;
		ofVec3f _pos, _near;
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