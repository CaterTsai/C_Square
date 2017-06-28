#pragma once

#include "DBase.h"

class DCylinderFlow : public DBase
{
#pragma region Flow Particle
	class flowParticle
	{
	public:
		flowParticle()
			:_cyPos(0)
			, _cyVec(0)
			, _cyAcc(0)
			, _ePos(0)
		{}
		
		void set(float p, float z, float vp, float vz);
		void update(float delta, ofVec2f desired);

	public:
		ofVec2f _cyPos, _cyVec, _cyAcc;
		ofVec3f _ePos;
	};
#pragma endregion

public:
	DCylinderFlow()
		:DBase(eDCylinderFlow)
	{
	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	
	void generateParticle();
	void generateFlowFields();
	void displayFlow(int x, int y, int w, int h);
	ofVec2f getFlow(ofVec2f cyPos);
	

private:
	array<DCylinderFlow::flowParticle, cDCNumber> _particleList;

	ofVec2f _flowFields[cDCFieldRows][cDCFieldCols];
};