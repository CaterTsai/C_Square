#pragma once

#include "DBase.h"

class DECA : public DBase
{
#pragma region stElement
	struct stElement{
		stElement()
		{
			ZeroMemory(_state, cCASize * sizeof(bool));
			ZeroMemory(_fromCode, cCASize * sizeof(int));
		}
		int _fromCode[cCASize];
		bool _state[cCASize];
	};
#pragma endregion
	
public:
	DECA()
		:DBase(eDECA)
		, _generationT(0.5f)
		, _baseColor(0, 255, 0)
	{
		_cCodeList[0] = 15;
		_cCodeList[1] = 22;
		_cCodeList[2] = 26;
		_cCodeList[3] = 30;
		_cCodeList[4] = 41;
		_cCodeList[5] = 45;
		_cCodeList[6] = 54;
		_cCodeList[7] = 60;
		_cCodeList[8] = 73;
		_cCodeList[9] = 90;
		_cCodeList[10] = 105;
		_cCodeList[11] = 106;
		_cCodeList[12] = 110;
		_cCodeList[13] = 120;
		_cCodeList[14] = 126;
		_cCodeList[15] = 146;
		_cCodeList[16] = 150;
		_cCodeList[17] = 154;
	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;
	void trigger() override;

	void setT(float time);
	void setColor(ofColor c);
private:
	void createWorld();
	void nextGeneration();
	int getCode(int x);
	void setCode(int value);

private:
	float _generationT;
	ofColor _baseColor;
	list<stElement>	_world;
	bool _decode[cCACodeSize];

	static int _cCodeList[cCATypeNum];
};