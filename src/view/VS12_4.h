#pragma once

#include "baseView.h"

class VS12_4 : public baseView
{
public:
	VS12_4(string path)
		:baseView(path)
	{}

	//-------------------------------
	void update(float delta) override
	{
		_dsp.update(delta);
		_dcf.update(delta);
	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
		{
			_dsp.draw(0, 0, _rect.width, _rect.height);
			_dcf.draw(0, 0, _rect.width * 0.5, _rect.height * 0.5);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
		{
			_dsp.draw(0, 0, _rect.width, _rect.height);
			_dcf.draw(0, 0, _rect.width * 0.5, _rect.height * 0.5);
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleLeftM);

		squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleRightM);
		ofEnableDepthTest();
		postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleRightM));
		{
			ofPushMatrix();
			ofScale(-1, 1);
			_dsp.draw(0, 0, _rect.width, _rect.height);
			_dcf.draw(0, 0, _rect.width * 0.5, _rect.height * 0.5);
			ofPopMatrix();
		}
		postFilter::GetInstance()->_squarePost.end();
		ofDisableDepthTest();
		squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);

		ofPopStyle();
	};

	//-------------------------------
	void drawMsg(ofVec2f pos) override
	{
		ostringstream ss;
		ss << "view 12-4\n";
		ofDrawBitmapStringHighlight(ss.str(), pos);
	}

	//-------------------------------
	void control(eCtrlType type, int value) override
	{
		
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		_dsp.setBaseSize(_rect.height * 0.4);
		_dsp.start();
		_dcf.start();
	}

	//-------------------------------
	void stop()
	{
		_dsp.stop();
		_dcf.stop();
	}

private:


private:
	DSphareParticle	_dsp;
	DCylinderFlow	_dcf;
	ofRectangle _rect;
	DDepthRect	_ddr;
};