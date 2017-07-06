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
		void update(float delta, ofVec3f force);
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
		, _forceCenter(0)
		, _forceValue(10.0)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;
	void trigger() override;
	void setBaseSize(float baseSize);

private:
	void initMetaBall();
	void drawBall();
	void addBallElement(int num);

	void updateCenter(float delta);

private:
	float _baseSize;
	list<ball> _ballList;

	ofxKMarchingCubes _mcubes;

	ofVec3f _forceCenter, _forceVec;
	float _forceValue;
};