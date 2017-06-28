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
const int cViewWindowHeight = 1024;

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
const int cCAMaxGeneration = 30;

//DCircleLine

//DSphareParticle
const int cDPNumber = 500;
const float cDPSpeedMin = 2 * DEG_TO_RAD;
const float cDPSpeedMax = 8 * DEG_TO_RAD;
const float cDPThetaMin = 30 * DEG_TO_RAD;
const float cDPThetaMax = 150 * DEG_TO_RAD;
const float cDPThetaMoveMin = 30 * DEG_TO_RAD;
const float cDPThetaMoveMax = 90 * DEG_TO_RAD;
const float cDPThetaLimit = 10 * DEG_TO_RAD;
const float cDPNearLimit = 0.2;

//DCylinderFlow
const int cDCNumber = 1000;
const int cDCFieldRows = 20;
const int cDCFieldCols = 50;
const float cDCPiSpeedMin = 10 * DEG_TO_RAD;
const float cDCPiSpeedMax = 20 * DEG_TO_RAD;
const float cDCZSpeedMin = 0.1;
const float cDCZSpeedMax = 0.3;
#pragma endregion


#pragma endregion

//---------------------------
#pragma region Static Method

#pragma endregion


