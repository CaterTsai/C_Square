#include "postFilter.h"

//-------------------------------------
void postFilter::init(int sw, int sh, int cw, int ch)
{
	if (_isInit)
	{
		return;
	}
	_squarePost.init(sw, sh);
	_canvasPost.init(cw, ch);

	_squarePost.createPass<BloomPass>()->setEnabled(false);
	_squarePost.createPass<BloomPass>()->setEnabled(false);
	_squarePost.createPass<NoiseWarpPass>()->setEnabled(false);
	_squarePost.createPass<ZoomBlurPass>()->setEnabled(false);
	_squarePost.createPass<KaleidoscopePass>()->setEnabled(false);
	_squarePost.createPass<EdgePass>()->setEnabled(false);
	_squarePost.createPass<PixelatePass>()->setEnabled(false);
	_squarePost.createPass<RGBShiftPass>()->setEnabled(false);
	_squarePost.createPass<ToonPass>()->setEnabled(false);

	_canvasPost.createPass<BloomPass>()->setEnabled(false);
	_canvasPost.createPass<BloomPass>()->setEnabled(false);
	_canvasPost.createPass<NoiseWarpPass>()->setEnabled(false);
	_canvasPost.createPass<ZoomBlurPass>()->setEnabled(false);
	_canvasPost.createPass<KaleidoscopePass>()->setEnabled(false);
	_canvasPost.createPass<EdgePass>()->setEnabled(false);
	_canvasPost.createPass<PixelatePass>()->setEnabled(false);
	_canvasPost.createPass<RGBShiftPass>()->setEnabled(false);
	_canvasPost.createPass<ToonPass>()->setEnabled(false);

	_isInit = true;
}

//-------------------------------------
void postFilter::squareEnable(ePostFilterType type, bool isEnable)
{
	_squarePost[(int)type]->setEnabled(isEnable);
}

//-------------------------------------
void postFilter::squareDisableAll()
{
	for (int i = 0; i < _squarePost.getNumProcessedPasses(); i++)
	{
		_squarePost[i]->disable();
	}
}

//-------------------------------------
void postFilter::canvasEnable(ePostFilterType type, bool isEnable)
{
	_canvasPost[(int)type]->setEnabled(isEnable);
}

//-------------------------------------
void postFilter::canvasDisableAll()
{
	for (int i = 0; i < _squarePost.getNumProcessedPasses(); i++)
	{
		_canvasPost[i]->disable();
	}
}

#pragma region Singleton
//--------------------------------------------------------------
postFilter* postFilter::pInstance = 0;
postFilter* postFilter::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new postFilter();
	}
	return pInstance;
}

//--------------------------------------------------------------
void postFilter::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion




