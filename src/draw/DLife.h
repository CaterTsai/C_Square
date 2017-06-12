#pragma once

#include "DBase.h"

class DLife : public DBase
{
public:
	DLife()
		:DBase(eDLife)
		,_generationT(0.1f)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void createWorld();
	void setPattern(int x, int y);
	void nextGeneration();
	void evolution(int x, int y);
	
private:
	float _generationT;
	bool* _nowGeneration;
	bool* _nextGeneration;
	bool _worldA[cWorldHeight * cWorldWidth];
	bool _worldB[cWorldHeight * cWorldWidth];
};