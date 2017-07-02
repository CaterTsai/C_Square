#pragma once

#include "DBase.h"
#include "ofxKMarchingCubes.h"
class DMetaBall3D : public DBase
{
private:
	class ball
	{
	public:
		ball(ofVec3f pos, ofVec3f vec, ofColor c, float size);
		void update(float delta);
		void checkLimit(float& p, float& v);

	public:
		ofVec3f _pos, _vec;
		ofColor _color;
		float _size;
	};

public:
	DMetaBall3D()
		:DBase(eDMetaBall3D)
		, _baseSize(1.0)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;
	void setBaseSize(float baseSize);

private:
	void initMetaBall();

private:
	float _baseSize;
	list<ball> _ballList;

	ofxKMarchingCubes _mcubes;
};