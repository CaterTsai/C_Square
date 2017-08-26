#pragma once

#include "baseView.h"
#include "VideoMgr.h"

class VS11_1 : public baseView
{
public:
	VS11_1(string path)
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
		_df.update(delta);
		_das.update(delta);

		switch (_eState)
		{
		case eAudioSphereGroup:
		{
			updateAudioSphereToGroup();
			break;
		}
		case eTexturePrimitiveGroup:
		{
			updateTexturePrimitiveToGroup();
			break;
		}
		}
	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		switch (_eState)
		{
		case eAudioSphereGroup:
		{
			drawTexturePrimitive();
			break;
		}
		case eTexturePrimitiveGroup:
		{
			drawAudioSphere();
			break;
		}
		}

		drawGroup();
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
		ss << "view 11-1\n";
		ss << "1 : Audio Sphere Group\n";
		ss << "2 : Texture Group\n";
		ss << "3 : Flash\n";
		ss << "4 : Texture Trigger\n";
		ss << "5 : Audio Sphere Toggle\n";
		ss << "6 : (L)Flash\n";
		ss << "7 : (L)Breath\n";

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
				_eState = eAudioSphereGroup;
				videoMgr::GetInstance()->stopAll();
				videoMgr::GetInstance()->play(eVideoMeiosis_4);
				_tex = videoMgr::GetInstance()->getTexture(eVideoMeiosis_4);
				_dtp.setTextrue((*_tex));

				_dtp.setBaseSize(_rect.getWidth() * 0.5);

				squareMgr::GetInstance()->clearAllSquare();
				squareMgr::GetInstance()->clearGroup();
			}
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			if (value == cMidiButtonPress)
			{
				_eState = eTexturePrimitiveGroup;
				videoMgr::GetInstance()->stopAll();
				videoMgr::GetInstance()->play(eVideoMeiosis_5);
				_tex = videoMgr::GetInstance()->getTexture(eVideoMeiosis_5);
				_dtp.setTextrue((*_tex));
				_dtp.setBaseSize(_canvas.getWidth() * 0.5);
				squareMgr::GetInstance()->clearAllSquare();
				squareMgr::GetInstance()->clearGroup();
			}
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			if (value == cMidiButtonPress)
			{
				_df.trigger();
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
		case eCtrl_ViewTrigger5:
		{
			if (value == cMidiButtonPress)
			{
				_das.toggleFace();
			}
			break;
		}
		case eCtrl_ViewTrigger6:
		{
			if (value == cMidiButtonPress)
			{
				LFlash flash;
				flash.time = static_cast<int>(60.0 / globalVariable::gBPM * 1000);
				flash.enable1 = true;
				flash.enable2 = true;
				flash.enable3 = true;
				flash.enable4 = true;
				sender::GetInstance()->sendAll(flash);
			}
			break;
		}
		case eCtrl_ViewTrigger7:
		{
			if (value == cMidiButtonPress)
			{
				LStopAll stopLight;
				sender::GetInstance()->sendAll(stopLight);

				LBreathe breathe;
				breathe.time = static_cast<int>(60.0 / globalVariable::gBPM * 1000);
				sender::GetInstance()->sendAll(breathe);
			}
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		videoMgr::GetInstance()->stopAll();
		videoMgr::GetInstance()->play(eVideoMeiosis_4);
		_tex = videoMgr::GetInstance()->getTexture(eVideoMeiosis_4);
		_df.start();
		_das.start();

		_dtp.setBaseSize(_rect.width * 0.5);
		_dtp.start();
		_eState = eAudioSphereGroup;

	}

	//-------------------------------
	void stop()
	{
		videoMgr::GetInstance()->stopAll();
		_df.stop();
		_das.stop();
		_dtp.stop();
	}

	//-------------------------------
	void setSoundValue(array<float, cBufferSize>& soundValue) override
	{
		_das.setSoundValue(soundValue);
	}

private:
	//-------------------------------
	void updateAudioSphereToGroup()
	{
		_canvas.begin();
		ofClear(0);

		postFilter::GetInstance()->_canvasPost.begin(camCtrl::GetInstance()->getCanvasCam());
		{
			ofSetDepthTest(true);
			_das.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
			ofSetDepthTest(false);
			_df.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
		}
		postFilter::GetInstance()->_canvasPost.end();
		_canvas.end();

		ofPixelsRef pix = _display.getPixelsRef();
		_canvas.readToPixels(pix);
		_display.update();
	}

	//-------------------------------
	void updateTexturePrimitiveToGroup()
	{
		_canvas.begin();
		ofClear(0);

		postFilter::GetInstance()->_canvasPost.begin(camCtrl::GetInstance()->getCanvasCam());
		{
			ofSetDepthTest(true);
			_tex->bind();
			_dtp.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
			_tex->unbind();
			ofSetDepthTest(false);
			_df.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
		}
		postFilter::GetInstance()->_canvasPost.end();
		_canvas.end();

		ofPixelsRef pix = _display.getPixelsRef();
		_canvas.readToPixels(pix);
		_display.update();
	}

	//-------------------------------
	void drawAudioSphere()
	{
		for (int i = 0; i < cSquareSmallNum; i++)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(i);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
			{
				_das.draw(0, 0, _rect.width, _rect.height);
				_df.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(i);
		}
	}

	//-------------------------------
	void drawTexturePrimitive()
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

				_df.draw(0, 0, _canvas.getWidth(), _canvas.getHeight());
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(i);
		}
	}

	//-------------------------------
	void drawGroup()
	{
		ofPushStyle();
		{
			squareMgr::GetInstance()->updateByGroup(_display);
		}
		ofPopStyle();
	}
private:
	enum eState
	{
		eAudioSphereGroup = 0
		, eTexturePrimitiveGroup
	}_eState;

	ofFbo	_canvas;
	ofImage	_display;

	DFlash	_df;
	DAudioSphere _das;

	ofTexture*	_tex;
	DTexturePrimitive	_dtp;
	ofRectangle _rect;

};