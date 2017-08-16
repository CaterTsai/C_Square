#include "squareMgr.h"
#include "ofxXmlSettings.h"

#pragma region Basic
//------------------------------
squareMgr::squareMgr()
	:_isSetup(false)
	,_ctrlID(-1)
	,_groupWidth(1920)
	,_groupHeight(1080)
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

	_isSetup = true;
}

//------------------------------
void squareMgr::displayUnitOnGroup(ofVec2f groupPos)
{
	//Draw Group
	ofPushMatrix();
	ofTranslate(groupPos);
	{
		ofPushStyle();
		ofNoFill();
		for (int i = 0; i < _squareList.size(); i++)
		{
			if (_squareList[i].type == eSquareGroup)
			{
				(i == _ctrlID) ? ofSetColor(255, 0, 0) : ofSetColor(255);
				ofDrawRectangle(_squareList[i].cropRange);
			}
		}
		ofPopStyle();
	}
	ofPopMatrix();
}

//------------------------------
void squareMgr::displayEachUnit(ofVec2f pos, int width)
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

	//Display Ctrl point
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
void squareMgr::clearSquare(int unitID)
{
	updateOnUnitBegin(unitID);
	ofClear(0);
	updateOnUnitEnd(unitID);
}

//------------------------------
void squareMgr::clearAllSquare()
{
	for (int i = 0; i < cSquareNum; i++)
	{
		clearSquare(i);
	}
}

//------------------------------
ofRectangle squareMgr::getUnitRect(int unitID)
{
	int size = _squareList.at(unitID).square.getSize();
	ofRectangle rect(0, 0, size, size);
	return rect;
}

//------------------------------
void squareMgr::saveConfig(string configName)
{
	ofxXmlSettings xml;

	for (int i = 0; i < cSquareNum; i++)
	{
		int squareSize = _squareList.at(i).square.getSize();
		xml.addTag("square");
		xml.pushTag("square", i);
		xml.addValue("UnitSize", squareSize);

		for (int j = 0; j < 4; j++)
		{
			auto ctrlPos = _squareList.at(i).square.getCtrlPos(j);
			xml.addTag("ctrlPos_" + ofToString(j + 1));
			xml.pushTag("ctrlPos_" + ofToString(j + 1));

			xml.addValue("x", ctrlPos.x);
			xml.addValue("y", ctrlPos.y);

			xml.popTag();
		}
		xml.popTag();
	}
	if (xml.saveFile(configName))
	{
		ofLog(OF_LOG_NOTICE, "[squareMgr::saveConfig]Save config success");
	}
	else
	{
		ofLog(OF_LOG_NOTICE, "[squareMgr::saveConfig]Save config failed");
	}
}

//------------------------------
void squareMgr::init(string configName)
{
	ofxXmlSettings xml;
	if (!xml.loadFile(configName))
	{
		ofLog(OF_LOG_ERROR, "[squareMgr::init]Load config failed :" + configName);
		return;
	}

	stSquareParam param;
	if (xml.getNumTags("square") != cSquareNum)
	{
		ofLog(OF_LOG_ERROR, "[squareMgr::init]wrong square number");
		return;
	}

	for (int i = 0; i < cSquareNum; i++)
	{	
		xml.pushTag("square", i);
		stSquareInfo newUnit;
		int squareSize = xml.getValue("UnitSize", 100, 0);

		newUnit.type = eSquareDrawType::eSquareIndependent;
		newUnit.cropRange.set(0, 0, squareSize, squareSize);
				
		for (int j = 0; j < 4; j++)
		{
			int x = xml.getValue("ctrlPos_" + ofToString(j + 1) + ":x", 0, 0);
			int y = xml.getValue("ctrlPos_" + ofToString(j + 1) + ":y", 0, 0);
			param.ctrlPos[j].set(x, y);
		}
		
		newUnit.square.setup(squareSize, param);
		_squareList.push_back(newUnit);
		xml.popTag();
	}

}
#pragma endregion

#pragma region On Group
//------------------------------
void squareMgr::setGroupSize(int width, int height)
{
	_groupWidth = width;
	_groupHeight = height;
}

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
					0, 0, unit.square.getSize(), unit.square.getSize(),
					unit.cropRange.x, unit.cropRange.y, unit.cropRange.width, unit.cropRange.height
				);
			}
			unit.square.drawEnd();
		}
	}
}

//------------------------------
void squareMgr::setUnitRect(int unitID, ofRectangle& rect)
{
	ofRectangle newRect = rect;
	if (newRect.getMinX() < 0)
	{
		newRect.setX(0);
	}
	if (newRect.getMaxX() > _groupWidth)
	{
		newRect.setX(_groupWidth - newRect.width);
	}
	if (newRect.getMinY() < 0)
	{
		newRect.setY(0);
	}
	if (newRect.getMaxY() > _groupHeight)
	{
		newRect.setY(_groupHeight - newRect.height);
	}

	_squareList.at(unitID).cropRange = newRect;
}

//------------------------------
void squareMgr::moveCropRect(int unitID, int x, int y)
{
	ofRectangle newRect;
	newRect.setFromCenter(x, y, _squareList.at(unitID).cropRange.width, _squareList.at(unitID).cropRange.height);
		
	if (newRect.getMinX() < 0)
	{
		newRect.setX(0);
	}
	if (newRect.getMaxX() > _groupWidth)
	{
		newRect.setX(_groupWidth - newRect.width);
	}
	if (newRect.getMinY() < 0)
	{
		newRect.setY(0);
	}
	if (newRect.getMaxY() > _groupHeight)
	{
		newRect.setY(_groupHeight - newRect.height);
	}

	_squareList.at(unitID).cropRange = newRect;
}
#pragma endregion

#pragma region On Unit
//------------------------------
void squareMgr::updateOnUnitBegin(int unitID, bool needClear)
{
	if (!_isSetup)
	{
		return;
	}
	if (_squareList.at(unitID).type == eSquareDrawType::eSquareIndependent)
	{
		_squareList.at(unitID).square.drawBegin(needClear);
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
void squareMgr::mouseDraggedFromView(int x, int y)
{
	if (_ctrlID != -1)
	{
		moveCropRect(_ctrlID, x, y);
	}
}


//------------------------------
void squareMgr::mousePressedFromProjector(int x, int y)
{
	if (_ctrlID != -1)
	{
		_squareList.at(_ctrlID).square.mousePress(x, y);
	}
}

//------------------------------
void squareMgr::mouseDraggedFromProjector(int x, int y)
{
	if (_ctrlID != -1)
	{
		_squareList.at(_ctrlID).square.mouseDrag(x, y);
	}
}

//------------------------------
void squareMgr::mouseReleasedFromProject(int x, int y)
{
	if (_ctrlID != -1)
	{
		_squareList.at(_ctrlID).square.mouseRelease(x, y);
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




