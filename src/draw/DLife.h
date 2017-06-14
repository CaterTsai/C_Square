#pragma once

#include "DBase.h"

class DLife : public DBase
{
#pragma region Life Element
	enum eLifeType
	{
		eNormal = 0
		,eStrong
		,eFast
		,eLifeNum
	};

	class LifeElement
	{
	public:
		LifeElement()
			:_live(false)
		{
			setType(eNormal);
		}

		inline bool getLive()
		{
			return _live;
		}
		inline void setLive(bool live)
		{
			_live = live;
		}

		inline eLifeType getType()
		{
			return _type;
		}

		void setType(eLifeType type);
		
		void evolution(int counter, eLifeType type);

	private:
		bool _live;
		eLifeType _type;
		int _liveMax, _liveMin;
		int _dieMax, _dieMin;
		int _generation;
	};
#pragma endregion


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
	LifeElement* _nowGeneration;
	LifeElement* _nextGeneration;
	LifeElement _worldA[cWorldHeight * cWorldWidth];
	LifeElement _worldB[cWorldHeight * cWorldWidth];
};