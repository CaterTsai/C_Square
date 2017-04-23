#include "squareMgr.h"

#pragma region Basic
//------------------------------
squareMgr::squareMgr()
	:_isSetup(false)
	,_ctrlID(-1)
{
}

//------------------------------
void squareMgr::setup(string configName)
{
	if (_isSetup)
	{
		ofLog(OF_LOG_ERROR, "[squareMgr::setup]setup already");
		return;
	}
	init(configName);
	ofRegisterMouseEvents(this);

	_isSetup = true;
}

//------------------------------
void squareMgr::drawOnGroup(ofVec2f groupPos)
{
	//Draw Group
	ofPushMatrix();
	ofTranslate(groupPos);
	{
		ofPushStyle();
		ofNoFill();
		for (auto& unit : _squareList)
		{
			if (unit.type == eSquareGroup)
			{
				ofDrawRectangle(unit.cropRange);
			}
		}
		ofPopStyle();
	}
	ofPopMatrix();
}

//------------------------------
void squareMgr::drawEachUnit(ofVec2f pos, int width)
{
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(pos);
	{
		float eachSize = (float)width / _squareList.size();
		for (int i = 0; i < _squareList.size(); i++)
		{
			_squareList[i].square.drawCanvas(i * eachSize, 0, eachSize);
		}
	}
	ofPopMatrix();
	ofPopStyle();
}

//------------------------------
void squareMgr::drawToProjection()
{
	ofPushStyle();
	for (auto& unit : _squareList)
	{
		unit.square.drawOnProjection();
	}
	ofPopStyle();

	if (_ctrlID != -1)
	{
		_squareList.at(_ctrlID).square.drawCtrlPos();
	}
}

//------------------------------
void squareMgr::setSquareType(int unitID, eSquareDrawType type)
{
	_squareList.at(unitID).type = type;
}

//------------------------------
void squareMgr::enableSquareControl(int unitID)
{
	_ctrlID = unitID;
}

//------------------------------
void squareMgr::disableSquareControl()
{
	_ctrlID = -1;
}

//------------------------------
void squareMgr::init(string configName)
{
	//TODO - change to config xml file
	stSquareParam param;
	
	stSquareInfo newUnit;
	newUnit.type = eSquareDrawType::eSquareIndependent;
	newUnit.cropRange.set(0, 0, 200, 200);
	
	param.ctrlPos[0] = ofVec2f(0, 0);
	param.ctrlPos[1] = ofVec2f(200, 0);
	param.ctrlPos[2] = ofVec2f(200, 200);
	param.ctrlPos[3] = ofVec2f(0, 200);
	newUnit.square.setup(200, param);
	_squareList.push_back(newUnit);

	stSquareInfo newUnit2;
	newUnit2.type = eSquareDrawType::eSquareGroup;
	newUnit2.cropRange.set(0, 0, 200, 200);

	param.ctrlPos[0] = ofVec2f(200, 200);
	param.ctrlPos[1] = ofVec2f(400, 200);
	param.ctrlPos[2] = ofVec2f(400, 400);
	param.ctrlPos[3] = ofVec2f(200, 400);
	newUnit2.square.setup(200, param);
	_squareList.push_back(newUnit2);
	
}
#pragma endregion


#pragma region On Group
//------------------------------
void squareMgr::updateByGroup(ofImage & groupCanvas)
{
	if (!_isSetup)
	{
		return;
	}

	for (auto& unit : _squareList)
	{
		if (unit.type == eSquareDrawType::eSquareGroup)
		{
			unit.square.drawBegin();
			{

				groupCanvas.drawSubsection(
					0, 0, unit.square.getWidth(), unit.square.getHeight(),
					unit.cropRange.x, unit.cropRange.y, unit.cropRange.width, unit.cropRange.height
				);
			}
			unit.square.drawEnd();
		}
	}
}
#pragma endregion


#pragma region On Unit
//------------------------------
void squareMgr::updateOnUnitBegin(int unitID)
{
	if (!_isSetup)
	{
		return;
	}
	if (_squareList.at(unitID).type == eSquareDrawType::eSquareIndependent)
	{
		_squareList.at(unitID).square.drawBegin();
	}
}

//------------------------------
void squareMgr::updateOnUnitEnd(int unitID)
{
	if (!_isSetup)
	{
		return;
	}
	if (_squareList.at(unitID).type == eSquareDrawType::eSquareIndependent)
	{
		_squareList.at(unitID).square.drawEnd();
	}
}
#pragma endregion

#pragma region Mouse
//------------------------------
void squareMgr::mousePressed(ofMouseEventArgs & e)
{
	if (_ctrlID != -1)
	{
		_squareList.at(_ctrlID).square.mousePress(e.x, e.y);
	}
}

//------------------------------
void squareMgr::mouseDragged(ofMouseEventArgs & e)
{
	if (_ctrlID != -1)
	{
		_squareList.at(_ctrlID).square.mouseDrag(e.x, e.y);
	}
}

//------------------------------
void squareMgr::mouseReleased(ofMouseEventArgs & e)
{
	if (_ctrlID != -1)
	{
		_squareList.at(_ctrlID).square.mouseRelease(e.x, e.y);
	}
}
#pragma endregion

#pragma region Singleton
//--------------------------------------------------------------
squareMgr* squareMgr::pInstance = 0;
squareMgr* squareMgr::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new squareMgr();
	}
	return pInstance;
}

//--------------------------------------------------------------
void squareMgr::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion




