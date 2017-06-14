#include "DECA.h"

//-------------------------------------
void DECA::update(float delta)
{
	CHECK_START();

	_timer -= delta;
	if (_timer <= 0.0f)
	{
		_timer = _generationT;
		nextGeneration();
	}
}

//-------------------------------------
void DECA::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	ofFill();
	{
		auto unitW = w / (float)cCASize;
		auto unitH = h / (float)cCAMaxGeneration;
		int ty = 0;
		for (auto& iter : _world)
		{
			int tx = 0;
			for (int i = 0; i < cCASize; i++)
			{
				if (iter._state[i])
				{
					ofColor green(0, 255, 0);
					green.setBrightness(green.limit() * (iter._fromCode[i] / (float)cCACodeSize));
					ofSetColor(green);

					//ofDrawRectangle(tx + x, ty + y, unitW, unitH);
					float r = unitW * 0.5;
					ofDrawCircle(tx + x + r, ty + y + r, r);
				}
				tx += unitW;
			}
			for (auto& state : iter._state)
			{
				if (state)
				{
					
				}
				
			}
			ty += unitH;
		}
	}
	ofPopStyle();
}

//-------------------------------------
void DECA::start()
{
	_isStart = true;
	_timer = _generationT;
	//setCode(rand() % 256);
	setCode(30);
	
	createWorld();
}

//-------------------------------------
void DECA::stop()
{
	_isStart = false;
}

//-------------------------------------
void DECA::createWorld()
{
	_world.clear();
	stElement firstGen;
	for (int i = 0; i < cCASize; i++)
	{
		if (rand() % 2 == 0)
		{
			firstGen._state[i] = true;
		}
	}
	_world.push_back(firstGen);
}

//-------------------------------------
void DECA::nextGeneration()
{
	stElement nextGen;
	for (int i = 0; i < cCASize; i++)
	{
		int code = getCode(i);
		nextGen._state[i] = _decode[code];
		nextGen._fromCode[i] = code;
	}
	_world.push_back(nextGen);

	if (_world.size() > cCAMaxGeneration)
	{
		_world.pop_front();
	}
}

//-------------------------------------
int DECA::getCode(int x)
{
	int values[3] = { 0 };
	values[1] = _world.back()._state[x];
	if (x + 1 >= cCASize)
	{
		values[0] = _world.back()._state[0];
	}
	else
	{
		values[0] = _world.back()._state[x + 1];
	}

	if (x - 1 < 0)
	{
		values[2] = _world.back()._state[cCASize - 1];
	}
	else
	{
		values[2] = _world.back()._state[x - 1];
	}

	int code = 0;
	for (int i = 0; i < 3; i++)
	{
		if (values[i])
		{
			code += (1 << i);
		}
	}
	return code;
}


//-------------------------------------
void DECA::setCode(int value)
{
	for (int i = 0; i < cCACodeSize; i++)
	{
		if (((value >> i) & 0x00000001) == 1)
		{
			_decode[i] = true;
		}
		else
		{
			_decode[i] = false;
		}
	}
}
