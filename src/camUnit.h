#pragma once

#include "constParameter.h"

enum eCamMoveType
{
	eCamFixed = 0
	, eCamRotate
	, eCamRotateBetween
	, eCamRevolution
	, eCamRevolutionBetween
	, eCamMoveBetween
	, eCamRandomOnBall
};

enum eCamMovePlayType
{
	eMoveOnce = 0,
	eMoveRepeat,
	eMoveRepeatBack
};

class camUnit
{
public:
	camUnit();
	void update(float delta);
	void drawCam(); //Debug
	void setPlayType(eCamMovePlayType type);
	void stop();
	void reset();


	void setFixed();
	void setFixed(ofVec3f& pos);

	void setRotate(float vec);
	void setRotate(float from, float to, float t);

	void setRevolution(ofVec3f& axis, float vec);
	void setRevolution(ofVec3f& axis, float from, float to, float t);

	void setMove(ofVec3f& to, float t);
	void setMove(ofVec3f& from, ofVec3f& to, float t);

	void setRandom(int dist, float t);

	void setTarget(ofVec3f& pos);

private:
	void updateRotate(float delta);
	void updateRevolution(float delta);
	void updateMove(float delta);
	void updateRandom(float delta);

	void setPorc(float t);
	void updatePrec(float delta);

private:
	static ofVec3f Spherical2Cartesian(ofVec3f pos);
	static ofVec3f Cartesian2Spherical(ofVec3f pos);

public:
	ofEasyCam _cam;

private:
	eCamMoveType _type;
	eCamMovePlayType _playType;

	ofVec3f _target;
	
	//Between
	float _prec, _v;
	
	//Rotate
	ofVec3f _axis;
	float _rVec;
	float _rAngle, _rFrom, _rTo;

	//Revolution
	ofVec3f _revAxis;
	float _revV;
	float _revAngle, _revFrom, _revTo; //Between
	
	//Move
	ofVec3f _posFrom, _posTo; //Between

	//Random
	float _timer, _randTime;
	float _dist;
};