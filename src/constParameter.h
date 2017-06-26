#pragma once

#include "ofMain.h"

//---------------------------
#pragma region Enum

#pragma endregion

//---------------------------
#pragma region Struct

#pragma endregion

//---------------------------
#pragma region Const Parameter
//--------------
//Window
const int cProjectionWindowWidth = 1920;
const int cProjectionWindowHeight = 1080;

const int cViewWindowWidth = 1024;
const int cViewWindowHeight = 760;

//--------------
//SquareUnit
const int cCtrlPointNum = 4;

const int cCtrlPointCircleRadius = cProjectionWindowHeight * 0.02;
const int cCtrlPointMaxDist = cCtrlPointCircleRadius;

//--------------
//Canvas
//const int cCanvasWidth = 1920;
//const int cCanvasHeight = 


#pragma region DElement
//DLife
const int cWorldWidth = 150;
const int cWorldHeight = 150;

//DECA
const int cCASize = 50;
const int cCACodeSize = 8;
const int cCAMaxGeneration = 50;

//DCircleLine

//DSphareParticle
const int cDPNumber = 1000;
const float cDPSpeedMin = 30 * DEG_TO_RAD;
const float cDPSpeedMax = 60 * DEG_TO_RAD;
const float cDPNearLimit = 0.3;

//DCylinderFlow
const int cDCNumber = 1000;
const int cDCFieldRows = 20;
const int cDCFieldCols = 20;
const float cDCPiSpeedMin = 30 * DEG_TO_RAD;
const float cDCPiSpeedMax = 60 * DEG_TO_RAD;
const float cDCZSpeedMin = 0.1;
const float cDCZSpeedMax = 0.3;
#pragma endregion


#pragma endregion

//---------------------------
#pragma region Static Method

#pragma endregion


