#pragma once

#include "DBase.h"

class DAudioSphere : public DBase
{
public:
	DAudioSphere()
		:DBase(eDAudioSphere)
		, _baseSize(100)
		, _audioScale(500)
	{

	}

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

	void setSoundValue(array<float, cBufferSize>& soundValue);

	void setSize(float size);
	inline void setScale(float scale)
	{
		_audioScale = scale;
	}
	inline void toggleFace()
	{
		_drawFace ^= true;
		swap(_faceColor, _lineColor);
	}

	//Set
	inline void setFace(int val)
	{
		_drawFace = val;
	}
	inline void setColor(ofColor& face, ofColor& line)
	{
		_faceColor = face;
		_lineColor = line;
	}

private:
	void resetSphere();

private:
	bool _drawFace;
	ofColor _faceColor, _lineColor;
	float _baseSize, _audioScale;
	ofIcoSpherePrimitive _sphere;
	vector<ofPoint> _verticesBackup;
	vector<float> _verticeValue;
};