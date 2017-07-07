#pragma once

#include "DBase.h"

class DPingPong : public DBase
{

#pragma region Ping-Pong Element
private:
	enum eBetType
	{
		eBetTop = 0
		,eBetLeft
		,eBetDown
		,eBetRight
	};

	class ball
	{
	public:
		ball();
		void update(float delta);
	public:
		bool _isDead;
		ofVec2f _pos, _vec;
	};

	class bet
	{
	public:
		bet() {};
		bet(eBetType type, float length);
		void update(float delta, list<ball>& ballList);

	private:
		bool getTouchPosAndTime(ball b, ofVec2f& pos, float &t);

	public:
		eBetType _type;
		ofVec2f _pos, _vec;
		ofVec2f _s, _e;
		float _length;
	};
#pragma endregion

public:
	DPingPong()
		:DBase(eDFlash)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	list<ball> _ballList;
	vector<bet> _bels;
};