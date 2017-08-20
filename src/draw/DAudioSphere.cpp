#include "DAudioSphere.h"

//---------------------------------------
void DAudioSphere::update(float delta)
{
	CHECK_START();
}

//---------------------------------------
void DAudioSphere::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	ofSetLineWidth(2);
	
	if (_drawFace)
	{
		ofSetColor(_faceColor);
		_sphere.draw();
	}
	ofSetColor(_lineColor);
	_sphere.drawWireframe();
	
	
	ofPopStyle();
}

//---------------------------------------
void DAudioSphere::start()
{
	_isStart = true;
	resetSphere();
}

//---------------------------------------
void DAudioSphere::stop()
{
	_isStart = false;
}

//---------------------------------------
void DAudioSphere::setSoundValue(array<float, cBufferSize>& soundValue)
{
	vector<ofPoint>& vertices = _sphere.getMesh().getVertices();
	vector<ofPoint>& normals = _sphere.getMesh().getNormals();


	for (int i = 0; i < _verticeValue.size(); i++)
	{
		int idx = i % cBufferSize;
		float inputValue = soundValue[idx] * _audioScale;
		//Update Value
		float value = (abs(inputValue) > _verticeValue[i]) ? inputValue : _verticeValue[i] * 0.95;
		
		if (abs(value) < 0.1)
		{
			value = 0;
		}
		_verticeValue[i] = value;

		//Update Vertex
		vertices[i] = _verticesBackup[i] + normals[i] * _verticeValue[i];
	}
}

//---------------------------------------
void DAudioSphere::setSize(float size)
{
	_baseSize = size;
	_sphere.setRadius(_baseSize);
}

//---------------------------------------
void DAudioSphere::resetSphere()
{
	_verticeValue.clear();
	_sphere = ofIcoSpherePrimitive();
	//_sphere.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINE_STRIP);
	_sphere.setRadius(_baseSize);
	_sphere.setResolution(3);

	_verticesBackup = _sphere.getMesh().getVertices();

	_verticeValue.resize(_verticesBackup.size());

}
