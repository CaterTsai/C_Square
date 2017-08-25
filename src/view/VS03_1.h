#pragma once

#include "baseView.h"

class VS03_1 : public baseView
{

public:
	VS03_1(string path)
		:baseView(path)
	{
		_canvas.allocate(cViewCanvasWidth, cViewCanvasHeight, GL_RGB);
		_display.allocate(cViewCanvasWidth, cViewCanvasHeight, ofImageType::OF_IMAGE_COLOR);

	}

	//-------------------------------
	void update(float delta) override
	{
		_djs.update(delta);
		_dam.update(delta);
		
		switch (_eState)
		{
		case eAudioMesh1:
		case eAudioMesh2:
		{
			updateAudioMesh();
			break;
		}
		case eJuliaSet:
		{
			updateJuliaSet();
			break;
		}
		}

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
			_eState = eAudioMesh1;
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_eState = eJuliaSet;
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			_eState = eAudioMesh2;
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			_dam.toggleBall();
			break;
		}
		case eCtrl_ViewTrigger5:
		{
			_dam.toggleLine();
			break;
		}
		case eCtrl_ViewTrigger6:
		{
			_djs.trigger();
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_dam.start();
		_dam.setLineNum(3);
		_djs.start();
		_eState = eAudioMesh1;
	}

	//-------------------------------
	void stop()
	{
		_djs.stop();
		_dam.stop();
	}

	//-------------------------------
	void setSoundValue(array<float, cBufferSize>& soundValue) override
	{
		_dam.setSoundValue(soundValue);
	}
private:
	void updateAudioMesh()
	{
		_canvas.begin();
		ofClear(0);
		postFilter::GetInstance()->_canvasPost.begin(camCtrl::GetInstance()->getCanvasCam());
		{
			_dam.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
		}
		postFilter::GetInstance()->_canvasPost.end();
		_canvas.end();

		ofPixelsRef pix = _display.getPixelsRef();
		_canvas.readToPixels(pix);
		_display.update();
	}

	void updateJuliaSet()
	{
		_canvas.begin();
		ofClear(0);
		postFilter::GetInstance()->_canvasPost.begin(camCtrl::GetInstance()->getCanvasCam());
		{
			_djs.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
		}
		postFilter::GetInstance()->_canvasPost.end();
		_canvas.end();

		ofPixelsRef pix = _display.getPixelsRef();
		_canvas.readToPixels(pix);
		_display.update();
	}


private:
	enum eState
	{
		eAudioMesh1 = 0
		,eJuliaSet
		,eAudioMesh2
	}_eState;
	DAudioMesh	_dam;
	DJuliaSet	_djs;
	ofFbo	_canvas;
	ofImage	_display;

	ofRectangle _squareMoveRange;
};