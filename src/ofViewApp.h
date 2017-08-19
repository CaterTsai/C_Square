#pragma once

#include "constParameter.h"
#include "scence.h"
#include "camCtrl.h"
#include "postFilter.h"

class ofViewApp : public ofBaseApp
{
public:
	ofViewApp()
		:_eDisplayType(eDisplayEach)
		, _isStart(false)
		, _targetSquare(true)
		, _soundSetup(false)
	{}
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);

	void control(eCtrlType ctrl, int value = 0);

private:
	float _mainTimer;
	enum eDisplayType
	{
		eDisplayEach = 0
		,eDisplayGroup
	}_eDisplayType;


//Scence
private:
	void initScence();
private:
	bool _isStart;
	vector<ofPtr<SBase>> _scenceMgr;
	eSType	_nowScence;

	//PostFilter
	bool _targetSquare;

//SoundStream
public:
	void setupSoundStream();
	void audioIn(float * input, int bufferSize, int nChannels);
private:
	bool _soundSetup;
	ofSoundStream	_soundStream;
	array<float, cBufferSize>	_soundValue;


};