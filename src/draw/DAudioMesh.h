#pragma once

#include "DBase.h"

class DAudioMesh : public DBase
{
public:
	DAudioMesh()
		:DBase(eDAudioMesh)
	{}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

private:
	void initPointMesh();

private:
	ofVec3f _pointMesh[cDAudioMeshRows][cDAudioMeshCols];
};