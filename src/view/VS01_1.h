#pragma once

#include "baseView.h"
#include "VideoMgr.h"
class VS01_1 : public baseView
{
public:
	VS01_1(string path)
		:baseView(path)
	{}

	//-------------------------------
	void update(float delta) override
	{
		videoMgr::GetInstance()->update();
		_ddr.update(delta);
		
	}

	//-------------------------------
	void draw(int width, int height) override
	{
		ofPushStyle();
		switch (_eState)
		{
		case eBass:
		{
			drawBass(_level);
			break;
		}
		case eBongo:
		{
			drawBongo(_level);
			break;
		}
		case eDrumAndBass:
		{
			drawDurmAndBass(_level);
			break;
		}
		case eDrumAndBassAndRect:
		{
			drawDurmAndBassAndRect(_level);
			break;
		}

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
			_eState = eBongo;
			_level = 0;
			videoMgr::GetInstance()->stopAll();
			videoMgr::GetInstance()->play(eVideoMeiosis_1);
			videoMgr::GetInstance()->play(eVideoBongo_2);
			videoMgr::GetInstance()->play(eVideoBongo_3);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger2:
		{
			_eState = eBass;
			_level = 0;
			videoMgr::GetInstance()->stopAll();
			videoMgr::GetInstance()->play(eVideoBass_1);
			videoMgr::GetInstance()->play(eVideoBass_2);
			videoMgr::GetInstance()->play(eVideoBass_3);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger3:
		{
			_eState = eDrumAndBass;
			_level = 0;
			videoMgr::GetInstance()->stopAll();
			videoMgr::GetInstance()->play(eVideoBass_1);
			videoMgr::GetInstance()->play(eVideoBass_2);
			videoMgr::GetInstance()->play(eVideoBass_3);
			videoMgr::GetInstance()->play(eVideoDrum_1);
			videoMgr::GetInstance()->play(eVideoDrum_2);
			videoMgr::GetInstance()->play(eVideoDrum_3);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger4:
		{
			_eState = eDrumAndBassAndRect;
			_level = 0;
			_ddr.start();
			videoMgr::GetInstance()->stopAll();
			videoMgr::GetInstance()->play(eVideoBass_1);
			videoMgr::GetInstance()->play(eVideoBass_2);
			videoMgr::GetInstance()->play(eVideoBass_3);
			videoMgr::GetInstance()->play(eVideoDrum_1);
			videoMgr::GetInstance()->play(eVideoDrum_2);
			videoMgr::GetInstance()->play(eVideoDrum_3);
			squareMgr::GetInstance()->clearAllSquare();
			
			
			break;
		}
		case eCtrl_ViewTrigger5:
		{
			_level = MIN(_level + 1, 2);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger6:
		{
			_level = MAX(_level - 1, 0);
			squareMgr::GetInstance()->clearAllSquare();
			break;
		}
		case eCtrl_ViewTrigger7:
		{
			_ddr.trigger();
			break;
		}
		}
	}

	//-------------------------------
	void start()
	{
		_rect = squareMgr::GetInstance()->getUnitRect(eSquareType::eBackCenerL);
		_level = 0;
		_eState = eBongo;
		
		videoMgr::GetInstance()->play(eVideoBongo_1);
		videoMgr::GetInstance()->play(eVideoBongo_2);
		videoMgr::GetInstance()->play(eVideoBongo_3);

		camCtrl::GetInstance()->_squareCams[eMiddleLeftM].setFixed(ofVec3f(-50, 0, 150));
		camCtrl::GetInstance()->_squareCams[eMiddleRightM].setFixed(ofVec3f(50, 0, 150));
	}

	//-------------------------------
	void stop()
	{
		videoMgr::GetInstance()->stopAll();
	}

private:
	//-------------------------------
	void drawBongo(int level) {

		if (level == 0)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
			{
				videoMgr::GetInstance()->draw(eVideoBongo_1, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);
		}
		else if (level == 1)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
			{
				videoMgr::GetInstance()->draw(eVideoBongo_3, _rect.width, _rect.height);
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
				videoMgr::GetInstance()->draw(eVideoBongo_3, _rect.width, _rect.height);
				ofPopMatrix();
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);


		}
		else if (level == 2)
		{
			for (int i = 0; i < cSquareSmallNum; i++)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					videoMgr::GetInstance()->draw(eVideoBongo_2, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}
		}
	}
	
	//-------------------------------
	void drawBass(int level) {

		if (level == 0)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
			{
				videoMgr::GetInstance()->draw(eVideoBass_1, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);
		}
		else if (level == 1)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
			{
				videoMgr::GetInstance()->draw(eVideoBass_3, _rect.width, _rect.height);
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
				videoMgr::GetInstance()->draw(eVideoBass_3, _rect.width, _rect.height);
				ofPopMatrix();
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);
		}
		else if (level == 2)
		{
			for (int i = 0; i < cSquareSmallNum; i++)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					videoMgr::GetInstance()->draw(eVideoBass_2, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}
		}
	}
	
	//-------------------------------
	void drawDurmAndBass(int level) {

		if (level == 0)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
			{
				videoMgr::GetInstance()->draw(eVideoDrum_1, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);

			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
			{
				videoMgr::GetInstance()->draw(eVideoBass_3, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleLeftM);

			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleRightM);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleRightM));
			{
				videoMgr::GetInstance()->draw(eVideoBass_3, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);
		}
		else if (level == 1)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
			{
				videoMgr::GetInstance()->draw(eVideoDrum_2, _rect.width, _rect.height);
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
				videoMgr::GetInstance()->draw(eVideoDrum_2, _rect.width, _rect.height);
				ofPopMatrix();
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);

			for (int i = 0; i < cSquareSmallNum; i++)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					videoMgr::GetInstance()->draw(eVideoBass_2, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}
		}
		else if (level == 2)
		{

			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
			{
				videoMgr::GetInstance()->draw(eVideoBass_2, _rect.width, _rect.height);
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
				videoMgr::GetInstance()->draw(eVideoBass_2, _rect.width, _rect.height);
				ofPopMatrix();
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);

			for (int i = 0; i < cSquareSmallNum; i++)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					videoMgr::GetInstance()->draw(eVideoDrum_3, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}
		}
	}

	//-------------------------------
	void drawDurmAndBassAndRect(int level) {

		if (level == 0)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
			{
				_ddr.draw(0, 0, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);

			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
			{
				videoMgr::GetInstance()->draw(eVideoDrum_2, _rect.width, _rect.height);
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
				videoMgr::GetInstance()->draw(eVideoDrum_2, _rect.width, _rect.height);
				ofPopMatrix();
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);

			for (int i = 0; i < cSquareSmallNum; i++)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					videoMgr::GetInstance()->draw(eVideoBass_2, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}
		}
		else if (level == 1)
		{
			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
			{
				videoMgr::GetInstance()->draw(eVideoBass_2, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);

			for (int i = 0; i < cSquareSmallNum; i++)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					videoMgr::GetInstance()->draw(eVideoDrum_2, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}

			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
			{
				_ddr.draw(0, 0, _rect.width, _rect.height);
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
				_ddr.draw(0, 0, _rect.width, _rect.height);
				ofPopMatrix();
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);
		}
		else if (level == 2)
		{

			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eBackCenerL);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eBackCenerL));
			{
				videoMgr::GetInstance()->draw(eVideoDrum_1, _rect.width, _rect.height);
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eBackCenerL);

			for (int i = 0; i < cSquareSmallNum; i++)
			{
				squareMgr::GetInstance()->updateOnUnitBegin(i);
				ofEnableDepthTest();
				postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(i));
				{
					_ddr.draw(0, 0, _rect.width, _rect.height);
				}
				postFilter::GetInstance()->_squarePost.end();
				ofDisableDepthTest();
				squareMgr::GetInstance()->updateOnUnitEnd(i);
			}

			squareMgr::GetInstance()->updateOnUnitBegin(eSquareType::eMiddleLeftM);
			ofEnableDepthTest();
			postFilter::GetInstance()->_squarePost.begin(camCtrl::GetInstance()->getSquareCam(eSquareType::eMiddleLeftM));
			{
				videoMgr::GetInstance()->draw(eVideoBass_3, _rect.width, _rect.height);
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
				videoMgr::GetInstance()->draw(eVideoBass_3, _rect.width, _rect.height);
				ofPopMatrix();
			}
			postFilter::GetInstance()->_squarePost.end();
			ofDisableDepthTest();
			squareMgr::GetInstance()->updateOnUnitEnd(eSquareType::eMiddleRightM);
		}
	}

	


private:
	enum eState
	{
		eBongo = 0
		, eBass
		, eDrumAndBass
		, eDrumAndBassAndRect

	}_eState;

	int _level;
	ofRectangle _rect;
	DDepthRect	_ddr;
};