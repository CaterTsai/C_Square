#include "squareUnit.h"

#pragma region Basic
//------------------------------
squareUnit::squareUnit()
	:_isSetup(false)
	, _startDraw(false)
{
}

//------------------------------
void squareUnit::setup(int size, const stSquareParam & param)
{
	_canvas.allocate(size, size, GL_RGBA);
	_canvas.getTextureReference().setTextureWrap(GL_REPEAT, GL_REPEAT);

	for (int i = 0; i < cCtrlPointNum; i++)
	{
		_ctrlPos[i].set(param.ctrlPos[i]);
	}

	setupPlane();

	_isSetup = true;
}

//------------------------------
void squareUnit::drawBegin(bool needClear)
{
	_startDraw = true;
	_canvas.begin();
	if (needClear)
	{
		ofClear(0);
	}	
}

//------------------------------
void squareUnit::drawEnd()
{
	_canvas.end();
	_startDraw = false;
}

//------------------------------
void squareUnit::drawCanvas(int x, int y, int size)
{
	if (!_isSetup || _startDraw)
	{
		return;
	}

	ofSetColor(255);
	_canvas.draw(x, y, size, size);
}

//------------------------------
int squareUnit::getSize()
{
	return _canvas.getWidth();
}

//------------------------------
ofVec2f squareUnit::getCtrlPos(int id)
{
	return _ctrlPos[id];
}


#pragma endregion


#pragma region Projection
//------------------------------
void squareUnit::drawOnProjection()
{
	ofPushStyle();
	ofSetColor(255);
	{
		_canvas.getTextureReference().bind();
		{
			_plane.draw();
		}
		_canvas.getTextureReference().unbind();
	}
	ofPopStyle();
}

//------------------------------
void squareUnit::mousePress(int x, int y)
{
	ofVec2f mousePos(x, y);
	float minDist = cCtrlPointMaxDist;
	int index = -1;
	for (int i = 0; i < cCtrlPointNum; i++)
	{
		float dist = _ctrlPos[i].distance(mousePos);
		if (dist < minDist)
		{
			minDist = dist;
			index = i;
		}
	}

	if (index != -1)
	{
		_selectCtrlIndex = index;
	}
}

//------------------------------
void squareUnit::mouseDrag(int x, int y)
{
	if (_selectCtrlIndex >= 0 && _selectCtrlIndex < cCtrlPointNum)
	{
		_ctrlPos[_selectCtrlIndex].set(x, y);
	}
}

//------------------------------
void squareUnit::mouseRelease(int x, int y)
{
	if (_selectCtrlIndex >= 0 && _selectCtrlIndex < cCtrlPointNum)
	{
		_plane.setVertex(_selectCtrlIndex, _ctrlPos[_selectCtrlIndex]);
	}
}


//------------------------------
void squareUnit::drawCtrlPos()
{
	ofPushStyle();
	{
		ofNoFill();
		ofSetLineWidth(3);
		ofSetColor(255, 0, 0);
		for (auto& pos : _ctrlPos)
		{
			ofCircle(pos, cCtrlPointCircleRadius);
		}
	}
	ofPopStyle();
}

//------------------------------
void squareUnit::setupPlane()
{
	_plane.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);
	_plane.enableTextures();

	for (int i = 0; i < cCtrlPointNum; i++)
	{
		_plane.addVertex(_ctrlPos[i]);
	}

	_plane.addTriangle(0, 1, 3);
	_plane.addTriangle(1, 2, 3);
	_plane.addTexCoord(ofVec2f(0.0, 0.0));
	_plane.addTexCoord(ofVec2f(200.0, 0.0));
	_plane.addTexCoord(ofVec2f(200.0, 200.0));
	_plane.addTexCoord(ofVec2f(0.0, 200.0));

	
}
#pragma endregion


