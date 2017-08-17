#pragma once

#include "baseView.h"

class VS06_1 : public baseView
{
private:
	class squarePos
	{
	public:
		void update(float delta, ofRectangle& range)
		{
			_pos += _vec * delta;
			if (_pos.x <= range.getMinX())
			{
				_pos.x = range.getMinX();
				_vec.x = -_vec.x;
			}
			else if (_pos.x > range.getMaxX())
			{
				_pos.x = range.getMaxX();
				_vec.x = -_vec.x;
			}

			if (_pos.y <= range.getMinY())
			{
				_pos.y = range.getMinY();
				_vec.y = -_vec.y;
			}
			else if (_pos.y >= range.getMaxY())
			{
				_pos.y = range.getMaxY();
				_vec.y = -_vec.y;
			}
		}
	
	public:
		ofVec2f _pos, _vec;
	};
public:
	VS06_1(string path)
		:baseView(path)
	{
		_canvas.allocate(cViewCanvasWidth, cViewCanvasHeight, GL_RGB);
		_display.allocate(cViewCanvasWidth, cViewCanvasHeight, ofImageType::OF_IMAGE_COLOR);

		_squareMoveRange.x = _squareCropRect[0].width * 0.5;
		_squareMoveRange.y = _squareCropRect[0].height * 0.5;
		_squareMoveRange.width = 500;
		_squareMoveRange.height = 600;
		for (int i = 0; i < cSquareNum; i++)
		{
			_squarePosList[i]._pos = _squareCropRect[i].getCenter();
			_squarePosList[i]._vec.x = ofRandom(0.01, 0.1) * 600 * (rand() % 2 == 0 ? 1: -1);
			_squarePosList[i]._vec.y = ofRandom(0.01, 0.1) * 600 * (rand() % 2 == 0 ? 1 : -1);
		}
		_needMove = false;
	}

	//-------------------------------
	void update(float delta) override
	{
		if (_needMove)
		{
			for (int i = 0; i < cSquareNum; i++)
			{
				_squarePosList[i].update(delta, _squareMoveRange);
				_squareCropRect[i].setFromCenter(
					_squarePosList[i]._pos
					, _squareCropRect[i].width
					, _squareCropRect[i].height
				);
				squareMgr::GetInstance()->setUnitRect(i, _squareCropRect[i]);
			}
		}
		
		_dms.update(delta);
		
		_canvas.begin();
		ofClear(0);
		postFilter::GetInstance()->_canvasPost.begin();
		{	
			_dms.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
		}
		postFilter::GetInstance()->_canvasPost.end();
		_canvas.end();

		ofPixelsRef pix = _display.getPixelsRef();
		_canvas.readToPixels(pix);
		_display.update();

	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		{	
			squareMgr::GetInstance()->updateByGroup(_display);
		}
		ofPopStyle();
	};

	//-------------------------------
	void drawCanvas(int x, int y, int width, int height) override
	{
		ofPushStyle();
		{
			_display.draw(x, y, width, height);
		}
		ofPopStyle();
	};

	//-------------------------------
	void control(eCtrlType type, int value) override
	{
		switch (type)
		{
		case eCtrl_ViewTrigger1:
		{
			_needMove = true;
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_needMove = false;
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_dms.start();
	}

	//-------------------------------
	void stop()
	{
		_dms.stop();
	}

private:
	DMandelbrotSet	_dms;
	ofFbo	_canvas;
	ofImage	_display;

	ofRectangle _squareMoveRange;

	bool _needMove;
	array<squarePos, cSquareNum> _squarePosList;
};