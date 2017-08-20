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
void videoMgr::add(eVideoType type, string file)
{

	if (_videos[type].load(file))
	{
		_videos[type].setLoopState(ofLoopType::OF_LOOP_NORMAL);
	}
	else
	{
		ofLog(OF_LOG_ERROR, "[videoMgr::add]Load video failed : " + file);
	}
}

//------------------------------------------------
void videoMgr::play(int id)
{
	if (id < 0 || id >= _videos.size())
	{
		return;
	}

	_videos[id].setFrame(0);
	_videos[id].play();
	_videos[id].update();
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
void videoMgr::stopAll()
{
	for (auto& iter : _videos)
	{
		iter.stop();
	}
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
