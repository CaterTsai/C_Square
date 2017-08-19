#pragma once

#include "DBase.h"

class DAudioMesh : public DBase
{
public:
	DAudioMesh()
		:DBase(eDAudioMesh)
		, _isDrawLine(false)
		, _isDrawBall(true)
	{
		setLineNum(2);
	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

	void setSoundValue(array<float, cBufferSize>& soundValue);

	void toggleLine();
	void toggleBall();
	void setLineNum(int val);
private:
	void initPointMesh();

private:
	bool _isDrawLine, _isDrawBall;
	bool _needDraw[cDAudioMeshRows];
	ofVec3f _pointMesh[cDAudioMeshRows][cDAudioMeshCols];
};