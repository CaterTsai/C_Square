#pragma once

#include "squareUnit.h"

enum eSquareDrawType
{
	eSquareGroup = 0
	, eSquareIndependent
	, eSquareInvisible
};

struct stSquareInfo
{
	stSquareInfo()
		:type(eSquareDrawType::eSquareGroup)
	{}

	eSquareDrawType type;
	ofRectangle	cropRange;
	squareUnit square;
};

class squareMgr
{
public:
	squareMgr();
	void setup(string configName = "");
	void displayUnitOnGroup(ofVec2f groupPos);
	void displayEachUnit(ofVec2f pos, int width);
	void drawToProjection();
	void setSquareType(int unitID, eSquareDrawType type);

	void enableSquareControl(int unitID);
	void disableSquareControl();
	
	ofRectangle getUnitRect(int unitID);

private:
	void init(string configName);
private:
	bool _isSetup;
	int _ctrlID;
	vector<stSquareInfo>	_squareList;

//Draw On Group
public:
	void setGroupSize(int width, int height);
	void updateByGroup(ofImage& groupCanvas);
	void moveUnitRect(int unitID, int x, int y);
private:
	int _groupWidth, _groupHeight;

//Draw On Unit
public:
	void updateOnUnitBegin(int unitID);
	void updateOnUnitEnd(int unitID);
	
//Mouse Event
public:
	void mouseDraggedFromView(int x, int y);

	void mousePressedFromProjector(int x, int y);
	void mouseDraggedFromProjector(int x, int y);
	void mouseReleasedFromProject(int x, int y);

//-------------------
//Singleton
//-------------------
public:
	static squareMgr* GetInstance();
	static void Destroy();

private:
	static squareMgr *pInstance;
};