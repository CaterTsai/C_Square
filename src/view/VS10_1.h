#pragma once

#include "baseView.h"

class VS10_1 : public baseView
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
	VS10_1(string path)
		:baseView(path)
	{
		_canvas.allocate(cViewCanvasWidth, cViewCanvasHeight, GL_RGB);
		_display.allocate(cViewCanvasWidth, cViewCanvasHeight, ofImageType::OF_IMAGE_COLOR);
	}

	//-------------------------------
	void update(float delta) override
	{
		_dmb.update(delta);

		_canvas.begin();
		ofClear(0);
		postFilter::GetInstance()->_canvasPost.begin(camCtrl::GetInstance()->getCanvasCam());
		{
			_dmb.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());

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
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "view 10-1\n";
		ss << "1 : Add Ball\n";
		ss << "2 : Toggle Draw Meta\n";
		ss << "3 : Toggle Draw Ball\n";
		ss << "4 : Toggle Draw Wireframe\n";
		ss << "5 : Random Cam\n";

		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	//-------------------------------
	void control(eCtrlType type, int value) override
	{
		switch (type)
		{
		case eCtrl_ViewTrigger1:
		{
			if (value == cMidiButtonPress)
			{
				_dmb.addBall();
			}
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			if (value == cMidiButtonPress)
			{
				_dmb.toggleDrawMetaball();
			}
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			if (value == cMidiButtonPress)
			{
				_dmb.toggleDrawBall();
			}
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			if (value == cMidiButtonPress)
			{
				_dmb.toggleDrawWireframe();
			}
			break;
		}
		case eCtrl_ViewTrigger5:
		{
			if (value == cMidiButtonPress)
			{
				camCtrl::GetInstance()->_canvasCam.setRandom();
			}
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_dmb.setBaseSize(cViewCanvasWidth);
		_dmb.start();
		_dmb.addBall();
	}

	//-------------------------------
	void stop()
	{
		_dmb.clearBall();
		_dmb.stop();
		
	}

private:
	ofRectangle _rect;
	DMetaBall3D	_dmb;
	ofFbo	_canvas;
	ofImage	_display;

};