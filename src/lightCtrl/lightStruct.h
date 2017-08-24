#pragma once

#include "sender.h"

class LBasic
{
public:
	LBasic(char l, char i, eLightCtrl t, short ti)
		:length(l)
		,id(i)
		, type(t)
		,time(ti)
	{}

	void toPackage(char* package)
	{
		package[1] = length;
		package[2] = id;
		package[3] = sender::getCmd(type);
		memcpy(package + 4, &time, 2);
	}
	unsigned char length, id;
	eLightCtrl	type;
	unsigned short time;
};

class LChangeColor : public LBasic
{
public:
	LChangeColor()
		:LBasic(5, 100, eChangeColor, 1000)
		, color(255, 0, 0)
	{}

	void toPackage(char* package)
	{
		package[1] = length;
		package[2] = id;
		package[3] = sender::getCmd(type);

		float h, s, b;
		color.getHsb(h, s, b);
		package[4] = ofMap(h, 0, color.limit(), 0, 255);
		package[5] = ofMap(s, 0, color.limit(), 0, 255);
		package[6] = ofMap(b, 0, color.limit(), 0, 255);
	}

	ofColor color;

};

class LFlash : public LBasic
{
public:
	LFlash()
		:LBasic(8, 0, ePlayOne, 1000)
		, enable1(true)
		, enable2(true)
		, enable3(true)
		, enable4(true)
	{}

	void toPackage(char* package)
	{
		package[1] = length;
		package[2] = id;
		package[3] = sender::getCmd(type);
		memcpy(package + 4, &time, 2);
		package[6] = enable1;
		package[7] = enable2;
		package[8] = enable3;
		package[9] = enable4;
	}

	
	bool enable1, enable2, enable3, enable4;
};

class LPointRandom : public LBasic
{
public:
	LPointRandom()
		:LBasic(4, 1, ePlayOne, 1000)
	{}
};

class LLineRandom : public LBasic
{
public:
	LLineRandom()
		:LBasic(4, 2, ePlayOne, 1000)
	{}
};

class LRunLine : public LBasic
{
public:
	LRunLine()
		: LBasic(5, 3, ePlayOne, 1000)
		, runType(0)
	{}

	void toPackage(char* package)
	{
		package[1] = length;
		package[2] = id;
		package[3] = sender::getCmd(type);
		memcpy(package + 4, &time, 2);
		package[6] = runType;
	}

	unsigned char runType;//0~4
};

class LOpen : public LBasic
{
public:
	LOpen()
		:LBasic(4, 4, ePlayOne, 1000)
	{}

};

class LRunLineCenter : public LBasic
{
public:
	LRunLineCenter()
		: LBasic(5, 5, ePlayOne, 1000)
		, runType(0)
	{}

	void toPackage(char* package)
	{
		package[1] = length;
		package[2] = id;
		package[3] = sender::getCmd(type);
		memcpy(package + 4, &time, 2);
		package[6] = runType;
	}
	unsigned char runType;//0~1
};