//
//  ofxKMarchingCubes.h
//  emptyExample
//
//  Created by Kamen Dimitrov on 12/8/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_ofxKMarchingCubes_h
#define emptyExample_ofxKMarchingCubes_h

#include "ofMain.h"


const int cGridResolution = 50;
const int cGridTotalNum = cGridResolution * cGridResolution * cGridResolution;
struct vec4 {
    ofVec3f vector;
    float value;
};

class ofxKMarchingCubes {

public:
	ofxKMarchingCubes();
	void setGrid(int size);
	void resetGrid();
	void update(float threshold, bool needColor = false);
	void draw(bool wireframe = false);
	void drawNormal();
	void drawGrid();

	void addMetaBall(ofVec3f center, float charge);
	void addMetaBall(ofVec3f center, float charge, ofColor color);


private:
	void updateMesh();
    // misc functions
    int getNumTriangles();
    
    // the heart of Marching Cubes
    void marchingCubes(int cubeX,int cubeY,int cubeZ, float threshold, bool needColor = false);
    void vertexInterpolation(float threshold, ofVec3f& p1, ofVec3f& p2, float valp1, float valp2, ofVec3f& vertex);
	void vertexInterpolation(
		float threshold, 
		ofVec3f& p1, ofVec3f& p2, 
		float valp1, float valp2,
		ofColor& c1, ofColor& c2,
		ofVec3f& vertex, ofColor& color);

    void getVec4(int index, int i, int j, int k,vec4 &v, ofColor &c);
    void getGradient(int index, int i, int j, int k,vec4 &v);
private:
	bool isSetup;

	ofVec3f gridCenter;
	float gridEachSize, gridHalf;

	ofColor gridColor_[cGridResolution][cGridResolution][cGridResolution];
	float gridIsoValuesAdd_[cGridResolution][cGridResolution][cGridResolution];
	float gridIsoValues_[cGridResolution][cGridResolution][cGridResolution];
	ofVec3f gridPoints_[cGridResolution][cGridResolution][cGridResolution];

    ofVec3f vertList[12];
	ofColor colorList[12];
    vec4 gradients[12];
    ofVec3f gradList[12];

	ofMesh grid;
    vector<ofVec3f> vertices;
    vector<ofColor> colors;
    vector<ofVec3f> normals;
    int numTriangles;
	int verticesIdx;
};


#endif
