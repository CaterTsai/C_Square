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

	class bet;
	class ball;

	class ball
	{
	public:
		ball();
		void update(float delta, vector<bet>& betList);
		
	public:
		bool _isDead, _isCross;
		ofVec2f _pos, _vec;
		ofColor _color;
		float _r;
	};

	class bet
	{
	public:
		bet() {};
		bet(eBetType type, float length);
		void update(float delta, list<ball>& ballList);
		void draw(float width, float height);

		void checkTouch(ball* b);

	private:
		bool getTouchPosAndTime(ball b, ofVec2f& pos, float &t);
		void limitCheck();

	public:
		eBetType _type;
		ofVec2f _pos, _vec;
		ofVec2f _s, _e;
		float _length, _halfL;
	};

	class ripple
	{
	public:
		ripple(ofVec2f pos, ofColor c);
		void update(float delta);
		void draw(float w);

	public:
		bool _isDead;
		ofVec2f _pos;
		ofColor _c;
		float _r, _rv;
	};

	class wire
	{
	public:
		wire();
		void update(float delta);
		void draw(float size);
		void reset();
		void set(ofVec2f start, ofVec2f end);
		void addWave(ofVec2f p);
	public:
		ofVec2f _s, _e;
		ofVec2f _moveV;
		float _wireNodes[cDPPWireNode];
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
	void initBoard();
	void addBall(int num);
	void addRipple(ofVec2f& pos, ofColor& c);
private:
	list<ball> _ballList;
	list<ripple> _rippleList;
	wire _hWire;
	vector<bet> _bels;
};