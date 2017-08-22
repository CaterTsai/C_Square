#pragma once

#include "baseView.h"

class VS09_2 : public baseView
{
public:
	VS09_2(string path)
		:baseView(path)
	{
		_canvas.allocate(cViewCanvasWidth, cViewCanvasHeight, GL_RGB);
		_display.allocate(cViewCanvasWidth, cViewCanvasHeight, ofImageType::OF_IMAGE_COLOR);
	}

	//-------------------------------
	void update(float delta) override
	{
		_dsp.update(delta);
		_dcf.update(delta);
		_canvas.begin();
		ofClear(0);
		postFilter::GetInstance()->_canvasPost.begin(camCtrl::GetInstance()->getCanvasCam());
		{
			switch (_eState)
			{
			case eShowSP:
			{
				_dsp.draw(0, 0, 0, 0);
				break;
			}
			case eShowCF:
			{
				_dcf.draw(0, 0, cViewCanvasWidth * 0.5, cViewCanvasHeight * 0.5);
				break;
			}
			case eShowBoth:
			{
				_dsp.draw(0, 0, 0, 0);
				_dcf.draw(0, 0, cViewCanvasWidth * 0.5, cViewCanvasHeight * 0.5);
				break;
			}
			}
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
			_eState = eShowSP;
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_eState = eShowCF;
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			_eState = eShowBoth;
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			_dsp.trigger();
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
		_dsp.setBaseSize(cViewCanvasHeight * 0.4);
		_dsp.start();
		_dcf.start();
		_eState = eShowSP;

		camCtrl::GetInstance()->_canvasCam.setRevolution(ofVec3f(0, -1, 0), PI * 0.2);
	}

	//-------------------------------
	void stop()
	{
		_dsp.stop();
		_dcf.stop();
	}

private:

private:
	enum eState
	{
		eShowSP = 0
		,eShowCF
		,eShowBoth
	}_eState;
	DSphareParticle	_dsp;
	DCylinderFlow	_dcf;
	ofFbo	_canvas;
	ofImage	_display;
};