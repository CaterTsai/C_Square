#include "DAudioMesh.h"

//-------------------------------------
void DAudioMesh::update(float delta)
{
	CHECK_START();

	for (int y = 0; y < cDAudioMeshRows; y++)
	{
		for (int x = 0; x < cDAudioMeshCols; x++)
		{
			_pointMesh[y][x].z = ofNoise(x, y) * 0.5;
		}
	}
}

//-------------------------------------
void DAudioMesh::draw(int x, int y, int w, int h)
{
	CHECK_START();

	float size = w * 0.005;
	ofVec3f temp;
	ofPushStyle();
	ofSetLineWidth(2);
	ofSetColor(255);
	{
		for (int y = 0; y < cDAudioMeshRows; y++)
		{
			for (int x = 0; x < cDAudioMeshCols; x++)
			{
				auto pos = _pointMesh[y][x] * w;
				if (x != 0)
				{
					ofLine(temp, pos);
				}
				
				ofDrawSphere(pos, size);
				temp = pos;
			}
		}
	}
	ofPopStyle();
}

//-------------------------------------
void DAudioMesh::start()
{
	_isStart = true;
	initPointMesh();
}

//-------------------------------------
void DAudioMesh::stop()
{
	_isStart = false;
}

//-------------------------------------
void DAudioMesh::initPointMesh()
{
	float yDelta = 1.0 / cDAudioMeshRows;
	float xDelta = 1.0 / cDAudioMeshCols;
	float posY = -0.5;
	float posX = -0.5;
	for (int y = 0; y < cDAudioMeshRows; y++)
	{
		posX = -0.5;
		for (int x = 0; x < cDAudioMeshCols; x++)
		{
			_pointMesh[y][x].set(posX, posY, 0.0f);
			posX += xDelta;
		}
		posY += yDelta;
	}
}

