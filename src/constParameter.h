#pragma once

#include "ofMain.h"

#define PROJECTION_MODE

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

const int cViewCanvasWidth = 1024;
const int cViewCanvasHeight = 1024;

const int cViewWindowWidth = 1024;
const int cViewWindowHeight = 1024;

//--------------
//Video Mgr
enum eVideoType : int
{
	eVideoDrum_1 = 0
	,eVideoDrum_2
	,eVideoDrum_3
	,eVideoBass_1
	,eVideoBass_2
	,eVideoBass_3
	,eVideoBongo_1
	,eVideoBongo_2
	,eVideoBongo_3
	,eVideoMeiosis_1
	,eVideoMeiosis_2
	,eVideoMeiosis_3
	,eVideoMeiosis_4
	,eVideoMeiosis_5
	,eVideoRotate
	,eVideoNum
};

//--------------
//Sound Stream
const int cBufferSize = 256;

//--------------
//SquareUnit
const int cCtrlPointNum = 4;

const int cCtrlPointCircleRadius = cProjectionWindowHeight * 0.02;
const int cCtrlPointMaxDist = cCtrlPointCircleRadius;
const int cSquareNum = 7;
const int cSquareSmallNum = 4;

enum eSquareType : int
{
	eFrontLeftS = 0
	, eFrontRightS
	, eBackLeftS
	, eBackRightS
	, eMiddleLeftM
	, eMiddleRightM
	, eBackCenerL
	
};
//--------------
//Canvas
//const int cCanvasWidth = 1920;
//const int cCanvasHeight = 


#pragma region DElement
//DLife
const int cWorldWidth = 150;
const int cWorldHeight = 150;

//DECA
const int cCASize = 30;
const int cCACodeSize = 8;
const int cCAMaxGeneration = 30;
const int cCATypeNum = 18;

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

//DDepthRect
const int cDDepthRectNum = 10;
const float cDDRotateMin = 30 * DEG_TO_RAD;
const float cDDRotateMax = 60 * DEG_TO_RAD;
const float cDDRotateDiffMin = 5 * DEG_TO_RAD;
const float cDDRotateDiffMax = 30 * DEG_TO_RAD;
const int cDDepthMax = 800;

//DStar
const int cDStarMaxNum = 500;
const float cDStarAddMinT = 0.1;
const float cDStarAddMaxT = 1.0;
const float cDStarMinV = 0.2;
const float cDStarMaxV = 0.5;
const float cDStarMovMin = 0.0;
const float cDStarMoveMax = 2.0;

//DMetaball3D

//DPingPong
const int cDPPBetNum = 4;
const int cDPPWireNode = 50;
const int cDPPWireHodeHalf = 25;

//DMandelbrotSet
const int cDMSCanvasWidth = 1024;
const int cDMSCanvasHeight = 1024;
const int cDMSMaximunCheck = 500;
const float cDMSZoomMax = 100000.0;
const int cDMSColorPatternNum = 6;
const int cDMSCenterNum = 15;
const pair<double, double> cDMSRealPartRange(-1.5, 1.5);
const pair<double, double> cDMSImaginePartRange(-1.5, 1.5);

//DJuliaSet
const int cDJSCanvasWidth = 600;
const int cDJSCanvasHeight = 600;
const int cDJSMaximunCheck = 100;
const int cDJSColorPatternNum = 10;
const pair<double, double> cDJSRealPartRange(-1.5, 1.5);
const pair<double, double> cDJSImaginePartRange(-1.5, 1.5);

//DAudioMesh
const int cDAudioMeshRows = 11;
const int cDAudioMeshCols = 50;

//DAudioSpere

//DAudioRect
const int cDAudioRectNum = MIN(64, cBufferSize);
const int cDAudioRectCheckSize = floor(cBufferSize / cDAudioRectNum);
const float cDAudioRectThreshold = .05;
#pragma endregion


#pragma endregion

//---------------------------
#pragma region Static Variable


#pragma endregion


