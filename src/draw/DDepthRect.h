#pragma once

#include "DBase.h"
#include "ofxAnimatableFloat.h"

class DDepthRect : public DBase
{
#pragma region Depth Rect
private:
	class depthRect
	{
	public:
		depthRect()
			:_color(255)
			,_display(false)
		{
			_animDepth.setRepeatType(AnimRepeat::PLAY_ONCE);
			_animRotate.setRepeatType(AnimRepeat::PLAY_ONCE);
		}

	public:
		void update(float delta);
		bool isDepthAnimFinish();
		void moveTo(float t, float depth);
		void moveToDelay(float t, float depth, float delay);
		void rotateTo(float t, float radin);
		void rotateToDelay(float t, float radin, float delay);


	public:
		bool _display;
		ofColor _color;

		ofxAnimatableFloat _animDepth, _animRotate;
	};
#pragma endregion

public:
	DDepthRect()
		:DBase(eDDepthRect)
		, _eState(eIdle)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;
	void trigger() override;

private:
	void initDepthList();
	void animCheck();
	void enter();
	void exit();
	void rotate();
	void rotateReset();

	void colorUpdate(float delta);

private:
	enum eState
	{
		eIdle = 0
		,eEnter
		,ePlay
		,eExit
	}_eState;
	float _depthMoveT;
	int _rectAnimIdx;
	vector<depthRect> _depthList;

	float _colorChangeT;
	int _colorIdx;

};