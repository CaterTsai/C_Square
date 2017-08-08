#pragma once

#include "constParameter.h"

struct stSquareParam
{
	ofVec2f ctrlPos[cCtrlPointNum];
};

class squareUnit
{

#pragma region Basic
public:
	squareUnit();
	void setup(int size, const stSquareParam& param);

	void drawBegin(bool needClear = true);
	void drawEnd();
	void drawCanvas(int x, int y, int size);

	int getSize();
	ofVec2f getCtrlPos(int id);

private:
	bool _isSetup, _startDraw;
	ofFbo _canvas;
#pragma endregion
	
#pragma region Projection
//on projection
public:
	void drawOnProjection();
	void mousePress(int x, int y);
	void mouseDrag(int x, int y);
	void mouseRelease(int x, int y);
	void drawCtrlPos();
private:
	void setupPlane();

private:
	int _selectCtrlIndex;
	ofVec2f _ctrlPos[cCtrlPointNum];
	ofMesh _plane;
#pragma endregion



};