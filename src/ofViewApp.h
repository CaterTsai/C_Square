#pragma once

#include "constParameter.h"
#include "scence.h"
#include "camCtrl.h"
#include "postFilter.h"
#include "videoMgr.h"
#include "midiCtrl.h"

class ofViewApp : public ofBaseApp, public ofxMidiListener
{
public:
	ofViewApp()
		:_isStart(false)
		, _targetSquare(true)
		, _soundSetup(false)
	{}
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);

	void control(eCtrlType ctrl, int value = cMidiButtonPress);

private:
	float _mainTimer;


//Scence
private:
	void initScence();
private:
	bool _isStart;
	vector<ofPtr<SBase>> _scenceMgr;
	eSType	_nowScence;

	//PostFilter
	bool _targetSquare;

//Video
public:
	void initVideo();

//Midi
public:
	void updateMidi();
	void newMidiMessage(ofxMidiMessage& msg) override;

private:
	struct midiCtrlData
	{
		eCtrlType type;
		int value;
	};
	list<midiCtrlData> _midiQueue;

//SoundStream
public:
	void setupSoundStream();
	void audioIn(float * input, int bufferSize, int nChannels);
private:
	bool _soundSetup;
	ofSoundStream	_soundStream;
	array<float, cBufferSize>	_soundValue;


};