#pragma once

#include "baseView.h"
#include "VideoMgr.h"

class VS05_2 : public baseView
{
public:
	VS05_2(string path)
		:baseView(path)
	{
		_canvas.allocate(cViewCanvasWidth, cViewCanvasHeight, GL_RGB);
		_display.allocate(cViewCanvasWidth, cViewCanvasHeight, ofImageType::OF_IMAGE_COLOR);
	}

	//-------------------------------
	void update(float delta) override
	{
		videoMgr::GetInstance()->update();
		_dtp.update(delta);
		_dl.update(delta);
		updateToCanvas();
	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		switch (_eState)
		{
		case eLifeOnly:
		{
			drawLife();
			break;
		}
		case eTextureOnly:
		{
			drawTexture();
			break;
		}
		case eBoth:
		{
			drawLife();
			drawTexture();
			break;
		}
		}
		ofPopStyle();
	};

	//-------------------------------
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "view 5-2\n";
		ss << "1 : Group Life \n";
		ss << "2 : Small Texture \n";
		ss << "3 : Both\n";
		ss << "4 : Texture Trigger\n";

		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

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
			if (value == cMidiButtonPress)
			{
				_eState = eLifeOnly;
				videoMgr::GetInstance()->stopAll();
				squareMgr::GetInstance()->clearAllSquare();
			}
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			if (value == cMidiButtonPress)
			{
				_eState = eTextureOnly;
				videoMgr::GetInstance()->stopAll();
				videoMgr::GetInstance()->play(eVideoMeiosis_4);
				_tex = videoMgr::GetInstance()->getTexture(eVideoMeiosis_4);
				_dtp.setTextrue((*_tex));
				squareMgr::GetInstance()->clearAllSquare();
				squareMgr::GetInstance()->clearGroup();
			}
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			if (value == cMidiButtonPress)
			{
				_eState = eBoth;
				videoMgr::GetInstance()->stopAll();
				videoMgr::GetInstance()->play(eVideoMeiosis_5);
				_tex = videoMgr::GetInstance()->getTexture(eVideoMeiosis_5);
				_dtp.setTextrue((*_tex));
				squareMgr::GetInstance()->clearAllSquare();
				squareMgr::GetInstance()->clearGroup();
			}
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			if (value == cMidiButtonPress)
			{
				_dtp.trigger();
			}
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		_dtp.setBaseSize(_rect.width * 0.5);
		_dtp.start();
		_dl.start();
		_eState = eLifeOnly;

		camCtrl::GetInstance()->_squareCams[eFrontLeftS].setRevolution(ofVec3f(-1, 1, 0), PI * 0.5);
		camCtrl::GetInstance()->_squareCams[eBackLeftS].setRevolution(ofVec3f(1, 1, 0), PI * 0.5);
		camCtrl::GetInstance()->_squareCams[eFrontRightS].setRevolution(ofVec3f(-1, -1, 0), PI * 0.5);
		camCtrl::GetInstance()->_squareCams[eBackRightS].setRevolution(ofVec3f(1, 1, 0), PI * 0.5);
	}

	//-------------------------------
	void stop()
	{
		videoMgr::GetInstance()->stopAll();
		_dtp.stop();
		_dl.stop();
	}

private:
	//-------------------------------
	void updateToCanvas()
	{
		_canvas.begin();
		ofClear(0);
		
		postFilter::GetInstance()->_canvasPost.begin();
		{
			_dl.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
		}
		postFilter::GetInstance()->_canvasPost.end();
		_canvas.end();

		ofPixelsRef pix = _display.getPixelsRef();
		_canvas.readToPixels(pix);
		_display.update();
	}

	//-------------------------------
	void drawLife()
	{
		ofPushStyle();
		{
			squareMgr::GetInstance()->updateByGroup(_display);
		}
		ofPopStyle();
	}

	//-------------------------------
	void drawTexture()
	{
		for (int i = 0; i < cSquareSmallNum; i++)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(i);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
			{
				_tex->bind();
				_dtp.draw(0, 0, _rect.width, _rect.height);
				_tex->unbind();
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(i);
		}
	}
private:
	enum eState
	{
		eLifeOnly = 0
		, eTextureOnly
		, eBoth
	}_eState;

	ofFbo	_canvas;	
	ofImage	_display;

	DLife	_dl;
	ofTexture*	_tex;
	DTexturePrimitive	_dtp;
	ofRectangle _rect;

};