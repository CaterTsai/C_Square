#pragma once

#include "constParameter.h"
#include "camUnit.h"

class camCtrl
{
public:
	void update(float delta);
	void displayPos(ofVec2f pos);
	void stopAll();
	void reset();
	ofEasyCam& getSquareCam(int id);
	ofEasyCam& getCanvasCam();
public:
	camUnit _canvasCam;
	array<camUnit, cSquareNum> _squareCams;

//-------------------
//Singleton
//-------------------
private:
	camCtrl() 
	{
		_canvasCam.setCamDefaultZ(886);
	};
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