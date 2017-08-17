#pragma once

#include "constParameter.h"
#include "camUnit.h"

class camCtrl
{
public:
	void update(float delta);
	void stopAll();
	ofEasyCam& getSquareCam(int id);
	ofEasyCam& getCanvasCam();
public:
	camUnit _canvasCam;
	array<camUnit, cSquareNum> _squareCams;

//-------------------
//Singleton
//-------------------
private:
	camCtrl() {};
	~camCtrl()
	{
		camCtrl::Destroy();
	}
	camCtrl(camCtrl const&);
	void operator=(camCtrl const&);

public:
	static camCtrl* GetInstance();
	static void Destroy();

private:
	static camCtrl *pInstance;
};