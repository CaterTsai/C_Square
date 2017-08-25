#pragma once

#include "ofMain.h"
#include "constParameter.h"
#include "ofxNetwork.h"

#define STA '\x01'
#define END '\x02'
#define SENDER_MAX 30

#define USE_NETWORK


enum eLightCtrl
{
	ePlayOne = 0
	,ePlayLoop
	,eStop
	,eChangeColor
};

class sender
{
public:

#ifdef USE_NETWORK
	void add(eSquareType type, string ip, int port);
#else // USE_NETWORK
	void add(eSquareType type, string port, int baud);
#endif//USE_NETWORK

	template<typename T>
	void send(eSquareType type, T data);

	template<typename T>
	void sendAll(T data);

	static char getCmd(eLightCtrl ctrl);
	
private:

#ifdef USE_NETWORK
	map<eSquareType, ofxUDPManager> _mgr;
#else // USE_NETWORK
	map<eSquareType, ofSerial> _mgr;
#endif // USE_NETWORK

//-------------------
//Singleton
//-------------------
private:
	sender() {};
	~sender()
	{
		sender::Destroy();
	}
	sender(sender const&);
	void operator=(sender const&);


public:
	static sender* GetInstance();
	static void Destroy();

private:
	static sender *pInstance;
};

template<typename T>
inline void sender::send(eSquareType type, T data)
{
	auto iter = _mgr.find(type);
	if (iter == _mgr.end())
	{
		return;
	}

	char msg[SENDER_MAX] = { 0 };
	msg[0] = STA;
	int length = data.length;
	data.toPackage(msg);
	msg[length + 2] = END;

#ifdef USE_NETWORK
	iter->second.Send(msg, SENDER_MAX);
#else USE_NETWORK
	if (iter->second.isInitialized())
	{
		iter->second.writeBytes((unsigned char*)msg, length + 3);
		iter->second.flush();
	}
	
#endif // USE_NETWORK	
};

template<typename T>
inline void sender::sendAll(T data)
{
	if (_mgr.size() == 0)
	{
		return;
	}

	char msg[SENDER_MAX] = { 0 };
	msg[0] = STA;
	int length = data.length;
	data.toPackage(msg);
	msg[length + 2] = END;

	for (auto& iter : _mgr)
	{
#ifdef USE_NETWORK
		iter.second.Send(msg, SENDER_MAX);
#else USE_NETWORK
		if (iter.second.isInitialized())
		{
			iter.second.writeBytes((unsigned char*)msg, length + 3);
			iter.second.flush();
		}
#endif // USE_NETWORK
	}
};
