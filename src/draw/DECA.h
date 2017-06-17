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
		, _generationT(0.1f)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void createWorld();
	void nextGeneration();
	int getCode(int x);
	void setCode(int value);

private:
	float _generationT;
	
	list<stElement>	_world;
	bool _decode[cCACodeSize];
};