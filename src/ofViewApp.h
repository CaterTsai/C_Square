#pragma once

#include "constParameter.h"
#include "scence.h"
#include "camCtrl.h"
#include "postFilter.h"

class ofViewApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);

private:
	float _mainTimer;

//Scence
private:
	STest	_testScence;
	S04		_scence04;
//SoundStream
public:
	void setupSoundStream();
	void audioIn(float * input, int bufferSize, int nChannels);
private:
	ofSoundStream	_soundStream;
	array<float, cBufferSize>	_soundValue;


};