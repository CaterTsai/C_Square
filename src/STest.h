#pragma once

#include "SBase.h"
#include "glitchFilter.h"
#include "ofxPostProcessing.h"

class STest : public SBase
{
public:
	STest()
		:SBase(eSTest)
		,_autoRotate(false)
	{
		setupPost();
	}

	void update(float delta) override;
	void draw() override;
	void start() override;
	void stop() override;

	void trigger();

private:
	ofRectangle _drawRect;
	DLife _life;
	DECA _eca;
	DCircleLine _cl;
	DSphareParticle _dp;
	DCylinderFlow _cf;
	DDepthRect	_dr;
	DStar _ds;
	DMetaBall3D _dm;
	DPingPong _dpp;
	DMandelbrotSet _dms;
	DJuliaSet _djs;


	//Camera
	bool _autoRotate;
	ofEasyCam	_cam;

//PostProcessing
private:
	void setupPost();

private:
	ofxPostProcessing _post;


};