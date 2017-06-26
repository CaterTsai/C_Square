#include "DCylinderFlow.h"

#pragma region flow Particle
//-------------------------------------
void DCylinderFlow::flowParticle::set(float p, float z, float vp, float vz)
{
	_cyPos.set(p, z);
	_cyVec.set(vp, vz);
	_cyAcc.set(0);
}

//-------------------------------------
void DCylinderFlow::flowParticle::update(float delta, ofVec2f desired)
{
	ofVec2f steer = desired - _cyVec;
	_cyVec += steer * delta;
	_cyPos += _cyVec * delta;

	_cyPos.x = (_cyPos.x >= TWO_PI) ? _cyPos.x - TWO_PI : (_cyPos.x < 0) ? _cyPos.x + TWO_PI : _cyPos.x;
	_cyPos.y = (_cyPos.y >= 1.0) ? _cyPos.y - 1.0 : (_cyPos.y < 0) ? _cyPos.y + 1.0 : _cyPos.y;

	_ePos.x = cos(_cyPos.x);
	_ePos.y = sin(_cyPos.x);
	_ePos.z = _cyPos.y;
}
#pragma endregion

//-------------------------------------
void DCylinderFlow::update(float delta)
{
	CHECK_START();

	for (auto& iter : _particleList)
	{
		iter.update(delta, getFlow(iter._cyPos));
	}
}

//-------------------------------------
void DCylinderFlow::draw(int x, int y, int w, int h)
{
	CHECK_START();

	ofPushStyle();
	ofSetColor(255);
	_cam.begin();
	{
		for (auto& iter : _particleList)
		{
			auto p = iter._ePos;
			p.x *= w;
			p.y *= w;
			p.z = ofMap(p.z, 0, 1, -0.5, 0.5) * h;

			ofDrawSphere(p, 5);
		}
	}
	_cam.end();
	ofPopStyle();
	//Debug
	//displayFlow(x, y, w, h);
}

//-------------------------------------
void DCylinderFlow::start()
{
	_isStart = true;
	generateParticle();
	generateFlowFields();
}

//-------------------------------------
void DCylinderFlow::stop()
{
	_isStart = false;
}

//-------------------------------------
void DCylinderFlow::generateParticle()
{
	ofSeedRandom();

	for (int i = 0; i < cDCNumber; i++)
	{
		_particleList[i].set(
			ofRandom(TWO_PI)
			, ofRandom(1.0)
			, ofRandom(cDCPiSpeedMin, cDCPiSpeedMax)
			, ofRandom(cDCZSpeedMin, cDCZSpeedMax)
		);
	}
}

//-------------------------------------
void DCylinderFlow::generateFlowFields()
{
	for (int i = 0; i < cDCFieldRows; i++)
	{
		for (int j = 0; j < cDCFieldCols; j++)
		{
			ofVec2f desired(ofMap(ofNoise(ofRandom(1.0)), 0, 1, -1, 1), ofMap(ofRandom(1.0), 0, 1, -1, 1));
			//ofVec2f desired(0.5, 0.5);
			_flowFields[i][j].set(desired.normalized());
		}
	}
}

//-------------------------------------
void DCylinderFlow::displayFlow(int x, int y, int w, int h)
{
	ofPushStyle();
	ofSetColor(255);
	ofFill();
	float unitW, unitH;
	unitW = w / cDCFieldCols;
	unitH = h / cDCFieldRows;

	for (int i = 0; i < cDCFieldRows; i++)
	{
		for (int j = 0; j < cDCFieldCols; j++)
		{
			ofVec2f center(i * unitH + unitH * 0.5, j * unitW + unitW * 0.5);
			ofVec2f desired = _flowFields[i][j];
			ofVec2f end = center + (desired * 0.5 * unitW);

			ofDrawCircle(center, 0.2 * unitW);
			ofLine(center, end);
		}
	}

	ofPopStyle();
}

//-------------------------------------
ofVec2f DCylinderFlow::getFlow(ofVec2f cyPos)
{
	int x = static_cast<int>(cyPos.x / TWO_PI * (cDCFieldCols));
	x = (x == cDCFieldCols) ? x - 1 : x;
	int y = static_cast<int>(cyPos.y * (cDCFieldRows));
	y = (y == cDCFieldRows) ? y - 1 : y;
	return _flowFields[y][x];
}


