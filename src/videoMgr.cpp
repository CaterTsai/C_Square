#include "videoMgr.h"

//------------------------------------------------
void videoMgr::update()
{
	for (auto& iter : _videos)
	{
		if (iter.isLoaded() && iter.isPlaying())
		{
			iter.update();
		}
	}
}

//------------------------------------------------
void videoMgr::draw(int id)
{
	if (_videos[id].isLoaded() && _videos[id].isPlaying())
	{
		ofPushStyle();
		ofSetColor(255);
		{
			_videos[id].draw(_videos[id].width * -0.5, _videos[id].height * -0.5);
		}
		ofPopStyle();
	}
}

//------------------------------------------------
void videoMgr::draw(int id, int w, int h)
{
	if (_videos[id].isLoaded() && _videos[id].isPlaying())
	{
		ofPushStyle();
		ofSetColor(255);
		{
			_videos[id].draw(w * -0.5, h * -0.5, w, h);
		}
		ofPopStyle();
	}
}

//------------------------------------------------
void videoMgr::add(string file)
{

}

//------------------------------------------------
void videoMgr::play(int id)
{
}

//------------------------------------------------
void videoMgr::stop(int id)
{
}

//------------------------------------------------
bool videoMgr::getTexture(int id, ofTexture & texture)
{
	return false;
}

//--------------------------------------------------------------
videoMgr* videoMgr::pInstance = 0;
videoMgr* videoMgr::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new videoMgr();
	}
	return pInstance;
}

//--------------------------------------------------------------
void videoMgr::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
