#include "DLife.h"

#pragma region Life Element
//-------------------------------------
void DLife::LifeElement::setType(eLifeType type)
{
	_type = type;
	_generation = 0;
	switch (type) {
		case eNormal:
		{
			_liveMax = 3;
			_liveMin = 2;
			_dieMax = 3;
			_dieMin = 3;
			break;
		}
		case eStrong:
		{
			_liveMax = 4;
			_liveMin = 3;
			_dieMax = 2;
			_dieMin = 1;
			break;
		}
		case eFast:
		{
			_liveMax = 3;
			_liveMin = 2;
			_dieMax = 3;
			_dieMin = 2;
			break;
		}
	}
}

//-------------------------------------
void DLife::LifeElement::evolution(int counter, eLifeType type)
{
	if (!_live)
	{
		if (counter <= _dieMax && counter >= _dieMin)
		{
			setType(type);
			setLive(true);
		}
	}
	else
	{
		if (counter > _liveMax || counter < _liveMin)
		{
			setLive(false);
		}
		else
		{
			if (_type == eNormal)
			{
				auto p = pow(0.995, _generation);
				if (ofRandom(0.0, 1.0) > p)
				{
					if (rand() % 2 == 0)
					{
						setType(eFast);
					}
					else
					{
						setType(eStrong);
					}
					
				}
			}
			_generation++;
		}
	}
}
#pragma endregion

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
				if (_nowGeneration[index].getLive())
				{
					ofColor color;
					switch (_nowGeneration[index].getType())
					{						
						case eNormal:
						{
							color.set(137, 207, 207);
							break;
						}
						case eStrong:
						{
							color.set(60, 150, 240);
							break;
						}
						case eFast:
						{
							color.set(232, 166, 113);
							break;
						}
					}
					ofSetColor(color);
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

	for (int tx = 0; tx < cWorldWidth; tx++)
	{
		for (int ty = 0; ty < cWorldHeight; ty++)
		{
			auto index = tx + ty * cWorldWidth;
			_nowGeneration[index].setType(eLifeType::eNormal);
			_nowGeneration[index].setLive(false);
		}
	}

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
			int rVal = rand() % 4;
			bool live = (rand() % 2 == 0);
			if (rVal == 0)
			{
				_nowGeneration[index].setType(eLifeType::eNormal);
			}
			else if(rVal == 1)
			{
				_nowGeneration[index].setType(eLifeType::eStrong);
			}
			else
			{
				_nowGeneration[index].setType(eLifeType::eFast);
			}
			_nowGeneration[index].setLive(live);
		}
	}
}

//-------------------------------------
void DLife::nextGeneration()
{
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
	int typeCounter[eLifeNum] = {0};
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

			if (_nowGeneration[index].getLive())
			{
				counter++;
				typeCounter[_nowGeneration[index].getType()]++;
			}
		}
	}

	int val = 0;
	eLifeType nextType;
	
	for (int i = 0; i < eLifeNum; i++)
	{
		if (typeCounter[i] > val)
		{
			val = typeCounter[i];
			nextType = (eLifeType)i;
		}
	}
	
	int index = x + y * cWorldWidth;
	_nextGeneration[index] = _nowGeneration[index];
	_nextGeneration[index].evolution(counter, nextType);
}