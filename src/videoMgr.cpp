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
int videoMgr::add(string file)
{
	ofxDSHapVideoPlayer	newVideo;
	if (newVideo.load(file))
	{
		_videos.push_back(newVideo);
		return _videos.size() - 1;
	}
	else
	{
		ofLog(OF_LOG_ERROR, "[videoMgr::add]Load video failed : " + file);
		return -1;
	}
}

//------------------------------------------------
void videoMgr::play(int id)
{
	if (id < 0 || id >= _videos.size())
	{
		return;
	}

	_videos[id].play();
}

//------------------------------------------------
void videoMgr::stop(int id)
{
	if (id < 0 || id >= _videos.size())
	{
		return;
	}

	_videos[id].stop();
}

//------------------------------------------------
bool videoMgr::getTexture(int id, ofTexture* texture)
{
	if (id < 0 || id >= _videos.size())
	{
		return false;
	}

	if (_videos[id].isPlaying())
	{
		texture = _videos[id].getTexture();
		return true;
	}
	else
	{
		return false;
	}
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
