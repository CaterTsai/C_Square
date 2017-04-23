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
	void drawOnGroup(ofVec2f groupPos);
	void drawEachUnit(ofVec2f pos, int width);
	void drawToProjection();
	void setSquareType(int unitID, eSquareDrawType type);

	void enableSquareControl(int unitID);
	void disableSquareControl();
	
private:
	void init(string configName);
private:
	bool _isSetup;
	int _ctrlID;
	vector<stSquareInfo>	_squareList;

//Draw On Group
public:
	void updateByGroup(ofImage& groupCanvas);
	
//Draw On Unit
public:
	void updateOnUnitBegin(int unitID);
	void updateOnUnitEnd(int unitID);
	
//Mouse Event
public:
	void mousePressed(ofMouseEventArgs& e);
	void mouseDragged(ofMouseEventArgs& e);
	void mouseReleased(ofMouseEventArgs& e);
	void mouseMoved(ofMouseEventArgs& e) {};
	void mouseScrolled(ofMouseEventArgs& e) {};
	void mouseEntered(ofMouseEventArgs& e) {};
	void mouseExited(ofMouseEventArgs& e) {};

//-------------------
//Singleton
//-------------------
public:
	static squareMgr* GetInstance();
	static void Destroy();

private:
	static squareMgr *pInstance;
};