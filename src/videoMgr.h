#pragma once

#include "constParameter.h"
#include "ofxDSHapVideoPlayer.h"

class videoMgr
{
public:
	void update();
	void draw(int id);
	void draw(int id, int w, int h);
	void add(eVideoType type, string file);
	void play(int id);
	void stop(int id);
	void stopAll();
	ofTexture* getTexture(int id);
private:

	vector<ofxDSHapVideoPlayer> _videos;

//-------------------
//Singleton
//-------------------
private:
	videoMgr() 
	{
		_videos.resize(eVideoNum);
	};
	~videoMgr()
	{
		videoMgr::Destroy();
	}
	videoMgr(videoMgr const&);
	void operator=(videoMgr const&);
	
public:
	static videoMgr* GetInstance();
	static void Destroy();

private:
	static videoMgr *pInstance;
};