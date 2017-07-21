#pragma once

#include "DBase.h"

class DTexturePrimitive : public DBase
{
private:
	enum ePrimitiveType : int
	{
		eSphere = 0
		,eIcoSphere
		,eBox
		,eTypeNum
	}_eType;

public:
	DTexturePrimitive();

	void update(float delta) override;
	void draw(int x, int y, int w, int h) override;

	void start() override;
	void stop() override;

	void trigger() override;

	void setBaseSize(float size);
	void setTextrue(ofTexture& tex);
	
private:
	void updatePrimitive(float delta);

private:
	of3dPrimitive* _primitive;
	ofSpherePrimitive _sphere;
	ofIcoSpherePrimitive _icoSphere;
	ofBoxPrimitive	_box;

	vector<ofMeshFace> _triangles;
};