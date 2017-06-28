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
			, _minT(0.0)
			, _maxT(0.0)
		{};

		particle(float t, float p, float vt, float vp, float maxT, float minT)
			:_t(t)
			,_p(p)
			,_amt(1.0)
			,_vt(vt)
			,_vp(vp)
			,_maxT(maxT)
			,_minT(minT)
		{}

		void set(float t, float p, float vt, float vp, float maxT, float minT);
		void setAmt(float amt);
		void update(float delta, float baseSize);
				
	public:
		float _t, _p;
		float _amt;
		float _vt, _vp;
		float _maxT, _minT;
		ofVec3f _pos;
	};
#pragma endregion


public:
	DSphareParticle()
		:DBase(eDSphereParticle)
		, _baseSize(1.0)
	{
		_tri.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLES);
		
	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;
	void trigger() override;
	void setBaseSize(float size);

private:
	void generateParticle();

	void computeTri();
private:
	float _baseSize;
	bool _triCheck[cDPNumber];
	array<DSphareParticle::particle, cDPNumber> _particleList;
	ofMesh _tri;
};