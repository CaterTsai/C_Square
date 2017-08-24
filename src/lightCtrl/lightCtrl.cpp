#include "lightCtrl.h"

//-------------------------------------
void lightCtrl::setType(int type)
{
	_type = type;
	ZeroMemory(_fxCheck, cFXNum);

	LChangeColor cc;
	if (type == 0)
	{
		cc.color = ofColor(0, 255, 0);
	}
	else
	{
		cc.color = ofColor(0, 0, 255);
	}

	sender::GetInstance()->sendAll(cc);
}

//-------------------------------------
void lightCtrl::enable()
{	
	ofRegisterKeyEvents(this);
}

//-------------------------------------
void lightCtrl::disable()
{
	ofUnregisterKeyEvents(this);
}

//-------------------------------------
void lightCtrl::keyPressed(ofKeyEventArgs & e)
{
	switch (e.key)
	{
		case 'a':
		{
			playEvent(0);
			break;
		}
		case 's':
		{
			playEvent(1);
			break;
		}
		case 'd':
		{
			playEvent(2);
			break;
		}
	}
}

//-------------------------------------
void lightCtrl::keyReleased(ofKeyEventArgs & e)
{
	switch (e.key)
	{
	case 'a':
	{
		releaseEvent(0);
		break;
	}
	case 's':
	{
		releaseEvent(1);
		break;
	}
	case 'd':
	{
		releaseEvent(2);
		break;
	}
	}
}

//-------------------------------------
void lightCtrl::idleLight()
{
	LRunLineCenter data;
	data.runType = 0;
	data.time = 500;
	sender::GetInstance()->sendAll(data);
}

//-------------------------------------
void lightCtrl::playEvent(int id)
{
	if (_fxCheck[id])
	{
		return;
	}

	if (_type == 0)
	{
		switch (id)
		{
		case 0:
		{
			LRunLine data;
			data.runType = 1;
			sender::GetInstance()->send(eFrontLeftS, data);
			break;
		}
		case 1:
		{
			LRunLineCenter data;			
			data.runType = 1;
			sender::GetInstance()->sendAll(data);
			break;
		}
		case 2:
		{
			LRunLine data;
			data.runType = 3;
			sender::GetInstance()->send(eFrontRightS, data);
			break;
		}
		}
	}
	else 
	{
		switch (id)
		{
		case 0:
		{
			LFlash data;
			data.time = 300;
			sender::GetInstance()->send(eFrontLeftS, data);
			break;
		}
		case 1:
		{
			LOpen data;
			data.time = 800;
			sender::GetInstance()->sendAll(data);
			break;
		}
		case 2:
		{
			LFlash data;
			data.time = 400;
			sender::GetInstance()->send(eFrontRightS, data);
			break;
		}
		}
	}
	_fxCheck[id] = true;
}

//-------------------------------------
void lightCtrl::releaseEvent(int id)
{
	if (_fxCheck[id])
	{
		_fxCheck[id] = false;
	}
}
