#include "DAudioMesh.h"

//-------------------------------------
void DAudioMesh::update(float delta)
{
	CHECK_START();

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
			if (!_needDraw[y])
			{
				continue;
			}
			for (int x = 0; x < cDAudioMeshCols; x++)
			{
				auto pos = _pointMesh[y][x] * w;
				if (_isDrawLine && x != 0)
				{
					ofLine(temp, pos);
				}
				if (_isDrawBall)
				{
					ofDrawSphere(pos, size);
				}
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
void DAudioMesh::setSoundValue(array<float, cBufferSize>& soundValue)
{
	for (int y = 0; y < cDAudioMeshRows; y++)
	{
		int startIdx = y * 2;
		int delta = rand() % 10;
		for (int x = 0; x < cDAudioMeshCols; x++)
		{
			float val = soundValue[(startIdx + x * delta) % cBufferSize] * 1.0f;
			if (val > _pointMesh[y][x].z)
			{
				_pointMesh[y][x].z = val;
			}
			else
			{
				_pointMesh[y][x].z *= 0.95;
			}
		}
	}
}

//-------------------------------------
void DAudioMesh::toggleLine()
{
	_isDrawLine ^= true;
}

//-------------------------------------
void DAudioMesh::toggleBall()
{
	_isDrawBall ^= true;
}

//-------------------------------------
void DAudioMesh::setLineNum(int val)
{
	ZeroMemory(_needDraw, sizeof(bool) * cDAudioMeshRows);
	int center = cDAudioMeshRows * 0.5;
	for (int i = 0; i < val; i++)
	{
		int idup = center + i;
		int iddown = center - i;
		_needDraw[idup] = true;
		_needDraw[iddown] = true;
	}
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

