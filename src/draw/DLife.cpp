#include "DLife.h"

//-------------------------------------
void DLife::update(float delta)
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
void DLife::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255);
	ofFill();
	{
		auto unitW = w / (float)cWorldWidth;
		auto unitH = h / (float)cWorldHeight;
		for (int tx = 0; tx < cWorldWidth; tx++)
		{
			for (int ty = 0; ty < cWorldHeight; ty++)
			{
				auto index = tx + ty * cWorldWidth;
				if (_nowGeneration[index])
				{
					ofDrawRectangle((tx * unitW) + x, (ty * unitH) + y, unitW, unitH);
				}
			}
		}
	}
	ofPopStyle();
}

//-------------------------------------
void DLife::start()
{
	_isStart = true;
	createWorld();
	
	_timer = _generationT;
}

//-------------------------------------
void DLife::stop()
{
	_isStart = false;
}

//-------------------------------------
void DLife::createWorld()
{
	_nowGeneration = _worldA;
	_nextGeneration = _worldB;
	ZeroMemory(_nowGeneration, cWorldHeight * cWorldWidth * sizeof(bool));
	ZeroMemory(_nextGeneration, cWorldHeight * cWorldWidth * sizeof(bool));

	int pNum = rand() % 30 + 20;
	for (int i = 0; i < pNum; i++)
	{
		int y = rand() % (cWorldHeight - 1) + 1;
		int x = rand() % (cWorldWidth - 1) + 1;
		setPattern(x, y);
	}
	
}

//-------------------------------------
void DLife::setPattern(int x, int y)
{
	for (int tx = x - 1; tx <= x + 1; tx++)
	{
		for (int ty = y - 1; ty <= y + 1; ty++)
		{
			int index = tx + ty * cWorldWidth;
			if (rand() % 2 == 0)
			{
				_nowGeneration[index] = true;
			}
			else
			{
				_nowGeneration[index] = false;
			}
		}
	}
}

//-------------------------------------
void DLife::nextGeneration()
{
	ZeroMemory(_nextGeneration, cWorldHeight * cWorldWidth * sizeof(bool));
	for (int x = 0; x < cWorldWidth; x++)
	{
		for (int y = 0; y < cWorldHeight; y++)
		{
			evolution(x, y);
		}
	}
	swap(_nowGeneration, _nextGeneration);
}

//-------------------------------------
void DLife::evolution(int x, int y)
{
	int counter = 0;
	for (int sx = -1; sx <= 1; sx++)
	{
		int tx = x + sx;
		tx = (tx < 0) ? (cWorldWidth + tx) : ((tx >= cWorldWidth) ? (tx - cWorldWidth) : tx);
		for (int sy = -1; sy <= 1; sy++)
		{
			if (sx == 0 && sy == 0)
			{
				continue;
			}

			int ty = y + sy;
			ty = (ty < 0) ? (cWorldHeight + ty) : ((ty >= cWorldHeight) ? (ty - cWorldHeight) : ty);
			int index = tx + ty * cWorldWidth;

			if (_nowGeneration[index])
			{
				counter++;
			}
			
		}
	}

	int index = x + y * cWorldWidth;
	if (_nowGeneration[index])
	{
		if (counter < 2)
		{
			_nextGeneration[index] = false;
		}
		else if (counter > 3)
		{
			_nextGeneration[index] = false;
		}
		else
		{
			_nextGeneration[index] = true;
		}
	}
	else
	{
		if (counter == 3)
		{
			_nextGeneration[index] = true;
		}
	}
}
