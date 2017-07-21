#include "DTexturePrimitive.h"

DTexturePrimitive::DTexturePrimitive()
	:DBase(eTexturePrimitive)
	, _primitive(nullptr)
{
	//Sphere
	_sphere.setRadius(1.0);
	_sphere.setResolution(16);
	_sphere.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLES);

	//Ico Sphere
	_icoSphere.setRadius(1.0);
	_icoSphere.setResolution(2);
	_icoSphere.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);

	//Box
	_box.set(1.0);
	_box.setResolution(6);
	_box.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);
	
	//Default display sphere
	_eType = eSphere;
	_primitive = &_sphere;
}

//---------------------------------------
void DTexturePrimitive::update(float delta)
{
	CHECK_START();
	updatePrimitive(delta);
}

//---------------------------------------
void DTexturePrimitive::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255);
	{
		_primitive->draw();
		//_primitive->drawWireframe();
	}
	ofPopStyle();
}

//---------------------------------------
void DTexturePrimitive::start()
{
	_isStart = true;
}

//---------------------------------------
void DTexturePrimitive::stop()
{
	_isStart = false;
}

//---------------------------------------
void DTexturePrimitive::trigger()
{
	_eType = (ePrimitiveType)((_eType + 1) % eTypeNum);
	switch (_eType)
	{
	case eSphere:
	{
		_primitive = &_sphere;
		break;
	}
	case eIcoSphere:
	{
		_primitive = &_icoSphere;
		break;
	}
	case eBox:
	{
		_primitive = &_box;
		break;
	}
	}
}

//---------------------------------------
void DTexturePrimitive::setBaseSize(float size)
{
	_sphere.setRadius(size);
	_icoSphere.setRadius(size);
	_box.set(size);
}

//---------------------------------------
void DTexturePrimitive::setTextrue(ofTexture & tex)
{
	_sphere.mapTexCoordsFromTexture(tex);
	_icoSphere.mapTexCoordsFromTexture(tex);
	_box.mapTexCoordsFromTexture(tex);
}

//---------------------------------------
void DTexturePrimitive::updatePrimitive(float delta)
{
	_triangles = _primitive->getMesh().getUniqueFaces();
	ofVec3f faceNormal;
	for (size_t i = 0; i < _triangles.size(); i++) {
		float angle = (ofGetElapsedTimef() * 1.4);
		float frc = ofSignedNoise(angle* (float)i * .1, angle*.05) * 10;
		faceNormal = _triangles[i].getFaceNormal();
		for (int j = 0; j < 3; j++) {
			_triangles[i].setVertex(j, _triangles[i].getVertex(j) + faceNormal * frc);
		}
	}
	_primitive->getMesh().setFromTriangles(_triangles);
}
