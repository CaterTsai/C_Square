#pragma once

#include "baseView.h"

class VS08_1 : public baseView
{
public:
	VS08_1(string path)
		:baseView(path)
	{
		_canvas.allocate(cViewCanvasWidth, cViewCanvasHeight, GL_RGB);
		_display.allocate(cViewCanvasWidth, cViewCanvasHeight, ofImageType::OF_IMAGE_COLOR);
	}

	//-------------------------------
	void update(float delta) override
	{
		_star.update(delta);

		_canvas.begin();
		ofClear(0);
		postFilter::GetInstance()->_canvasPost.begin(camCtrl::GetInstance()->getCanvasCam());
		{
			_star.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
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
			break;
		}
		case eCtrl_ViewTrigger2:
		{
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
		case eCtrl_ViewTrigger5:
		{

			break;
		}
		case eCtrl_ViewTrigger6:
		{

			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_star.start();

	}

	//-------------------------------
	void stop()
	{

	}

private:

private:
	ofFbo	_canvas;
	ofImage	_display;
	DStar	_star;
};