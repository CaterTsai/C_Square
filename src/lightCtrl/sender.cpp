#include "sender.h"

//--------------------------------------------------------------
#ifdef USE_NETWORK
void sender::add(eSquareType type, string ip, int port)
{
	if (_mgr.find(type) != _mgr.end())
	{
		ofLog(OF_LOG_ERROR, "[sender::add]Duplicate type");
		return;
	}

	ofxUDPManager newUdp;
	_mgr.insert(make_pair(type, newUdp));
	_mgr[type].Create();
	_mgr[type].Connect(ip.c_str(), port);
	_mgr[type].SetNonBlocking(true);
}

#else //USE_NETWORK
//--------------------------------------------------------------
void sender::add(eSquareType type, string port, int baud)
{
	if (_mgr.find(type) != _mgr.end())
	{
		ofLog(OF_LOG_ERROR, "[sender::add]Duplicate type");
		return;
	}

	if (port != "")
	{
		_mgr[type] = ofSerial();
		_mgr[type].setup(port, baud);
	}
	
	
	
}
#endif //USE_NETWORK


char sender::getCmd(eSquareType ctrl)
{
	char r = 't';
	switch (ctrl)
	{
		case ePlayOne:
		{
			r = 't';
			break;
		}
		case ePlayLoop:
		{
			r = 'p';
			break;
		}
		case eStop:
		{
			r = 's';
			break;
		}
		case eChangeColor:
		{
			r = 'c';
			break;
		}
	}
	return r;
}


//--------------------------------------------------------------
sender* sender::pInstance = 0;
sender* sender::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new sender();
	}
	return pInstance;
}

//--------------------------------------------------------------
void sender::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}