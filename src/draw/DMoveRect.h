#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"
class DMoveRect : public DBase
{

private:
	enum eEnterDirection : int
	{
		eEnterUp = 0
		,eEnterDown
		,eEnterLeft
		,eEnterRight
	};
	enum eExitDirection : int
	{
		eExitDown = 0
		, eExitUp
		, eExitRight
		, eExitLeft
	};
public:
	DMoveRect()
		:DBase(eDMoveRect)
		, _groupNum(2)
	{}

	void update(float delta) override;
	void draw(int id, int x, int y, int w, int h);

	void start() override;
	void stop() override;

	void trigger() override;
	void setGroupNum(int num);

private:
	int _groupNum;
	int _nowID, _enterID, _exitID;
	ofColor _nowColor, _enterColor, _exitColor;
	ofxAnimatableFloat _animMove;
};