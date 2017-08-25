#include "ofViewApp.h"

//--------------------------------------------------------------
void ofViewApp::setup()
{
	ofBackground(23, 24, 26);
	ofSetCircleResolution(60);
	//ofEnableSmoothing();
	//ofDisableArbTex();
	
	initVideo();
	initScence();

	//Singleton
	squareMgr::GetInstance()->setup("config/_squareConfig.xml");
	postFilter::GetInstance()->init(200, 200, cViewCanvasWidth, cViewCanvasWidth);
	postFilter::GetInstance()->_squarePost.setFlip(false);
	ofSetFrameRate(60);
	setupSoundStream();
	
	_mainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofViewApp::update()
{
	float delta = ofGetElapsedTimef() - _mainTimer;
	_mainTimer += delta;

	
	camCtrl::GetInstance()->update(delta);
	_scenceMgr[_nowScence]->update(delta);

	if (_soundSetup)
	{
		_scenceMgr[_nowScence]->setSoundValue(_soundValue);
	}

	
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofViewApp::draw()
{
	ofSetBackgroundColor(0);
	_scenceMgr[_nowScence]->draw();

	switch (_eDisplayType)
	{
	case eDisplayEach:
	{
		squareMgr::GetInstance()->displayEachUnit(ofVec2f(0, 0), 1024);
		break;
	}
	case eDisplayGroup:
	{
		_scenceMgr[_nowScence]->drawCanvas(0, 0, 1024, 1024);
		squareMgr::GetInstance()->displayUnitOnGroup(ofVec2f(0, 0));
		break;
	}
	}

	string filterMsg = (_targetSquare ? "Square" : "Canvas");
	ofDrawBitmapStringHighlight("Scence :" + _scenceMgr[_nowScence]->getScenceName(), ofVec2f(0, 15));
	ofDrawBitmapStringHighlight("Filter Target :" + filterMsg, ofVec2f(0, 30));

	//Debug
	camCtrl::GetInstance()->displayPos(ofVec2f(0, 45));
}

//--------------------------------------------------------------
void ofViewApp::keyPressed(int key)
{	
	eCtrlType type = ctrlMap::GetInstance()->key2Ctrl[key];
	if (type >= 0 && type < eCtrl_GlobalNum)
	{
		control(type);
	}
	else
	{
		_scenceMgr[_nowScence]->control(type);
	}
	
}

//--------------------------------------------------------------
void ofViewApp::mouseDragged(int x, int y, int button)
{
	squareMgr::GetInstance()->mouseDraggedFromView(x, y);
}

//--------------------------------------------------------------
void ofViewApp::control(eCtrlType ctrl, int value)
{
	switch (ctrl)
	{
	case eCtrl_Start:
	{
		_scenceMgr[_nowScence]->start();
		_isStart = true;
		break;
	}
	case eCtrl_Stop:
	{
		_scenceMgr[_nowScence]->stop();
		_isStart = false;
		break;
	}
	case eCtrl_NextScence:
	{
		auto nextScence = (eSType)((_nowScence + 1) % eSTypeNum);
		if (_isStart)
		{
			_scenceMgr[_nowScence]->stop();
			_scenceMgr[nextScence]->start();
		}
		_nowScence = nextScence;
		squareMgr::GetInstance()->clearAllSquare();
		camCtrl::GetInstance()->reset();
		break;
	}
	case eCtrl_PrevScence:
	{
		auto nextScence = (eSType)((_nowScence - 1) % eSTypeNum);
		if (nextScence < 0)
		{
			nextScence = (eSType)(eSTypeNum - 1);
		}
		if (_isStart)
		{
			_scenceMgr[_nowScence]->stop();
			_scenceMgr[nextScence]->start();
		}
		_nowScence = nextScence;
		squareMgr::GetInstance()->clearAllSquare();
		camCtrl::GetInstance()->reset();
		break;
	}
	case eCtrl_DisplayEach:
	{
		_eDisplayType = eDisplayEach;
		break;
	}
	case eCtrl_DisplayGroup:
	{
		_eDisplayType = eDisplayGroup;
		break;
	}
#pragma region Filter
	case eCtrl_ChangeFilterTarget:
	{
		_targetSquare ^= true;
		break;
	}
	case eCtrl_DisableAllFilter:
	{
		postFilter::GetInstance()->disableAll();
		break;
	}
	case eCtrl_Filter1:
	{
		postFilter::GetInstance()->filterEnable(_targetSquare, ePostFilterType::ePostBloom);
		break;
	}
	case eCtrl_Filter2:
	{
		postFilter::GetInstance()->filterEnable(_targetSquare, ePostFilterType::ePostBloomTwo);
		break;
	}
	case eCtrl_Filter3:
	{
		postFilter::GetInstance()->filterEnable(_targetSquare, ePostFilterType::ePostEdge);
		break;
	}
	case eCtrl_Filter4:
	{
		postFilter::GetInstance()->filterEnable(_targetSquare, ePostFilterType::ePostKaleidoscope);
		break;
	}
	case eCtrl_Filter5:
	{
		postFilter::GetInstance()->filterEnable(_targetSquare, ePostFilterType::ePostNoiseWarp);
		break;
	}
	case eCtrl_Filter6:
	{
		postFilter::GetInstance()->filterEnable(_targetSquare, ePostFilterType::ePostPixel);
		break;
	}
	case eCtrl_Filter7:
	{
		postFilter::GetInstance()->filterEnable(_targetSquare, ePostFilterType::ePostRGBShift);
		break;
	}
	case eCtrl_Filter8:
	{
		postFilter::GetInstance()->filterEnable(_targetSquare, ePostFilterType::ePostToon);
		break;
	}
	case eCtrl_Filter9:
	{
		postFilter::GetInstance()->filterEnable(_targetSquare, ePostFilterType::ePostZoomBlur);
		break;
	}
	}
#pragma endregion

	
}

//--------------------------------------------------------------
void ofViewApp::initScence()
{
	_scenceMgr.push_back(ofPtr<SIdle>(new SIdle()));
	_scenceMgr.push_back(ofPtr<S01>(new S01()));
	_scenceMgr.push_back(ofPtr<S02>(new S02()));
	_scenceMgr.push_back(ofPtr<S03>(new S03()));
	_scenceMgr.push_back(ofPtr<S04>(new S04()));
	_scenceMgr.push_back(ofPtr<S05>(new S05()));
	_scenceMgr.push_back(ofPtr<S06>(new S06()));
	_scenceMgr.push_back(ofPtr<S07>(new S07()));
	_scenceMgr.push_back(ofPtr<S08>(new S08()));
	_scenceMgr.push_back(ofPtr<S09>(new S09()));
	_scenceMgr.push_back(ofPtr<S10>(new S10()));
	_scenceMgr.push_back(ofPtr<S11>(new S11()));

	_nowScence = eS09;
}

//--------------------------------------------------------------
void ofViewApp::initVideo()
{
	videoMgr::GetInstance()->add(eVideoDrum_1, "videos/dm_1.avi");
	videoMgr::GetInstance()->add(eVideoDrum_2, "videos/dm_2.avi");
	videoMgr::GetInstance()->add(eVideoDrum_3, "videos/dm_3.avi");
	videoMgr::GetInstance()->add(eVideoBass_1, "videos/bass_1.avi");
	videoMgr::GetInstance()->add(eVideoBass_2, "videos/bass_2.avi");
	videoMgr::GetInstance()->add(eVideoBass_3, "videos/bass_3.avi");
	videoMgr::GetInstance()->add(eVideoBongo_1, "videos/bg_1.avi");
	videoMgr::GetInstance()->add(eVideoBongo_2, "videos/bg_2.avi");
	videoMgr::GetInstance()->add(eVideoBongo_3, "videos/bg_3.avi");
	videoMgr::GetInstance()->add(eVideoMeiosis_1, "videos/meiosis_1.avi");
	videoMgr::GetInstance()->add(eVideoMeiosis_2, "videos/meiosis_2.avi");
	videoMgr::GetInstance()->add(eVideoMeiosis_3, "videos/meiosis_3.avi");
	videoMgr::GetInstance()->add(eVideoMeiosis_4, "videos/meiosis_4.avi");
	videoMgr::GetInstance()->add(eVideoMeiosis_5, "videos/meiosis_5.avi");
	videoMgr::GetInstance()->add(eVideoRotate, "videos/rotate.avi");
}

//--------------------------------------------------------------
void ofViewApp::setupSoundStream()
{	
	_soundStream.setDeviceID(1);
	_soundSetup = _soundStream.setup(this, 0, 2, 44100, cBufferSize, 4);
	
}

//--------------------------------------------------------------
void ofViewApp::audioIn(float * input, int bufferSize, int nChannels)
{
	for (int i = 0; i < cBufferSize; i++)
	{
		_soundValue[i] = (input[i * 2] + input[i * 2 + 1]) * 0.5;
	}
}

