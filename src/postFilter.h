#pragma once

#include "constParameter.h"
#include "ofxPostProcessing.h"

enum ePostFilterType
{
	ePostBloom = 0
	,ePostBloomTwo
	,ePostNoiseWarp
	,ePostZoomBlur
	,ePostKaleidoscope
	,ePostEdge
	,ePostPixel
	,ePostRGBShift
	,ePostToon
};

class postFilter
{
public:
	void init(int sw, int sh, int cw, int ch);
	void filterEnable(bool isSquare, ePostFilterType type);
	void filterEnable(bool isSquare, ePostFilterType type, bool isEnable);
	void disableAll();
private:
	bool _isInit;

public:
	ofxPostProcessing _squarePost, _canvasPost;
//-------------------
//Singleton
//-------------------
private:
	postFilter()
		:_isInit(false)
	{};
	~postFilter()
	{
		postFilter::Destroy();
	}
	postFilter(postFilter const&);
	void operator=(postFilter const&);

public:
	static postFilter* GetInstance();
	static void Destroy();

private:
	static postFilter *pInstance;
};