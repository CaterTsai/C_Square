#pragma once

#include "SBase.h"
#include "camCtrl.h"
#include "postFilter.h"

class STest : public SBase
{
public:
	STest();

	void update(float delta) override;
	void draw() override;
	void start() override;
	void stop() override;

	void control(eCtrlType ctrl, int value = 0) override;

#pragma region View
//View
private:
	void initView() override;
	void setView(int id) override;

private:
	void view1Draw();
	void view2Draw();

#pragma endregion

//Draw Element
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
	DTexturePrimitive _dtp;
	DAudioMesh	_dam;
	DMoveRect _dmr;

private:
	ofImage _img;

};