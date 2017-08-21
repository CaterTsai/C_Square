//
//  ofxKMarchingCubes.cpp
//  emptyExample
//
//  Created by Kamen Dimitrov on 12/8/11.
//  Based on: http://paulbourke.net/geometry/polygonise/
//
#include "ofxKMarchingCubes.h"
#include "ofxKMarchingCubesTables.h"

//----------------------------------
ofxKMarchingCubes::ofxKMarchingCubes()
	:gridEachSize(1.0/ cGridResolution)
	, gridHalf (0.5)
	, gridCenter(0)
	, isSetup(false)
{}

//----------------------------------
void ofxKMarchingCubes::setGrid(int size) 
{
	gridEachSize = (float)size / cGridResolution;
	gridHalf = size * 0.5;
	resetGrid();
	grid.setMode(OF_PRIMITIVE_TRIANGLES);
}

//----------------------------------
void ofxKMarchingCubes::resetGrid()
{
	ZeroMemory(gridIsoValues_, cGridTotalNum * sizeof(float));
	ZeroMemory(gridIsoValuesAdd_, cGridTotalNum * sizeof(float));
	ofVec3f pos = gridCenter - gridHalf;
	for (int x = 0; x < cGridResolution; x++) {
		for (int y = 0; y < cGridResolution; y++) {
			for (int z = 0; z < cGridResolution; z++) {
				gridPoints_[x][y][z] = ofVec3f(pos.x + x * gridEachSize, pos.y + y * gridEachSize, pos.z + z * gridEachSize);
				gridColor_[x][y][z].set(0);
			}
		}
	}
}

//----------------------------------
void ofxKMarchingCubes::draw(bool wireframe) 
{    
	if (wireframe)
	{
		grid.drawWireframe();
	}
	else
	{
		grid.drawFaces();
	}
}

//----------------------------------
void ofxKMarchingCubes::drawNormal()
{
	ofMesh nm;
	nm.setMode(OF_PRIMITIVE_LINES);
	for(int i=0;i < numTriangles; i++) {
	    nm.addVertex(vertices[i*3]);
	    nm.addVertex(vertices[i*3]+normals[i*3]*40);
	    nm.addVertex(vertices[i*3+1]);
	    nm.addVertex(vertices[i*3+1]+normals[i*3+1]*40);
	    nm.addVertex(vertices[i*3+2]);
	    nm.addVertex(vertices[i*3+2]+normals[i*3+2]*40);
	}
	nm.drawWireframe();
}

//----------------------------------
void ofxKMarchingCubes::drawGrid()
{
	ofPushStyle();
	ofSetColor(255);
	ofNoFill();
	ofBox(gridCenter, gridHalf * 2);

	ofPopStyle();
}

//----------------------------------
void ofxKMarchingCubes::addMetaBall(ofVec3f center, float charge) {
	ofVec3f diff;
	for (int x = 0; x < cGridResolution; x++) {
		for (int y = 0; y < cGridResolution; y++) {
			for (int z = 0; z < cGridResolution; z++) {
				auto val = charge / gridPoints_[x][y][z].distance(center);
				gridIsoValues_[x][y][z] += val;
			}
		}
	}
}

//----------------------------------
void ofxKMarchingCubes::addMetaBall(ofVec3f center, float charge, ofColor color) {
    ofVec3f diff;
    for(int x=0; x < cGridResolution; x++) {
        for(int y=0; y < cGridResolution; y++) {
            for(int z = 0; z < cGridResolution; z++) {
				auto val = charge / gridPoints_[x][y][z].distance(center);
				gridIsoValues_[x][y][z] += val;
				if (gridIsoValuesAdd_[x][y][z] < val)
				{
					gridIsoValuesAdd_[x][y][z] = val;
					gridColor_[x][y][z] = color;
				}
            }
        }
    }    
}

//----------------------------------
void ofxKMarchingCubes::updateMesh()
{
	int vnum = grid.getNumVertices();
	int cnum = grid.getNumColors();
	

	for (int i = 0; i < numTriangles; i++) {
		int index = i * 3;
		if ((index + 2) >= vnum)
		{
			grid.addVertex(vertices[index]);
			grid.addVertex(vertices[index + 1]);
			grid.addVertex(vertices[index + 2]);
		}
		else
		{
			grid.setVertex(index, vertices[index]);
			grid.setVertex(index + 1, vertices[index + 1]);
			grid.setVertex(index + 2, vertices[index + 2]);
		}

		if ((index + 2) >= cnum)
		{
			grid.addColor(colors[index]);
			grid.addColor(colors[index + 1]);
			grid.addColor(colors[index + 2]);
		}
		else
		{
			grid.setColor(index, colors[index]);
			grid.setColor(index + 1, colors[index + 1]);
			grid.setColor(index + 2, colors[index + 2]);
		}

	}
	int index = numTriangles * 3;
	for (int i = vnum - 1; i >= index; i--)
	{
		grid.removeVertex(i);
		grid.removeColor(i);
	}
}

//----------------------------------
void ofxKMarchingCubes::update(float threshold, bool needColor) {
    
	numTriangles = 0;
	verticesIdx = 0;
    for(int x=0; x < cGridResolution -1; x++) {
        for(int y=0; y < cGridResolution -1; y++) {
            for(int z = 0; z < cGridResolution -1; z++) {
                marchingCubes(x, y, z, threshold, needColor);
            }
        }
    }
	updateMesh();
}

//----------------------------------
int ofxKMarchingCubes::getNumTriangles() {
    return numTriangles;
}

//----------------------------------
void ofxKMarchingCubes::getVec4(int index, int i, int j, int k,vec4 &v, ofColor &c) {
    switch(index) {
        case 0:
            v.vector = gridPoints_[i][j][k];
            v.value = gridIsoValues_[i][j][k];
			c = gridColor_[i][j][k];
        break;
        case 1:
            v.vector = gridPoints_[i+1][j][k];
            v.value = gridIsoValues_[i+1][j][k];
			c = gridColor_[i + 1][j][k];
            break;
        case 2:
            v.vector = gridPoints_[i+1][j][k+1];
            v.value = gridIsoValues_[i+1][j][k+1];
			c = gridColor_[i + 1][j][k + 1];
            break;
        case 3:
            v.vector = gridPoints_[i][j][k+1];
            v.value = gridIsoValues_[i][j][k+1];
			c = gridColor_[i][j][k + 1];
            break;
        case 4:
            v.vector = gridPoints_[i][j+1][k];
            v.value = gridIsoValues_[i][j+1][k];
			c = gridColor_[i][j + 1][k];
            break;
        case 5:
            v.vector = gridPoints_[i+1][j+1][k];
            v.value = gridIsoValues_[i+1][j+1][k];
			c = gridColor_[i + 1][j + 1][k];
            break;
        case 6:
            v.vector = gridPoints_[i+1][j+1][k+1];
            v.value = gridIsoValues_[i+1][j+1][k+1];
			c = gridColor_[i + 1][j + 1][k + 1];
            break;
        case 7:
            v.vector = gridPoints_[i][j+1][k+1];
            v.value = gridIsoValues_[i][j+1][k+1];
			c = gridColor_[i][j + 1][k + 1];
            break;
        
    }
}

//----------------------------------
void ofxKMarchingCubes::getGradient(int index, int i, int j, int k,vec4 &v) {
   
    switch(index) {
        case 0:
            if(i != 0 && j != 0 && k != 0) { 
                v.vector = ofVec3f(
                    gridIsoValues_[i-1][j][k] - gridIsoValues_[i+1][j][k],
                    gridIsoValues_[i][j-1][k] - gridIsoValues_[i][j+1][k],
                    gridIsoValues_[i][j][k-1] - gridIsoValues_[i][j][k+1]);
                   v.value = gridIsoValues_[i][j][k];
            } else {
                v.vector = ofVec3f(0.0,0.0,0.0);
                v.value = 1.0;
            }
            break;
            
        case 1:
            if(i < cGridResolution -2 && j != 0 && k != 0) {
                v.vector = ofVec3f(
                                   gridIsoValues_[i+1-1][j][k] - gridIsoValues_[i+1+1][j][k],
                                   gridIsoValues_[i+1][j-1][k] - gridIsoValues_[i+1][j+1][k],
                                   gridIsoValues_[i+1][j][k-1] - gridIsoValues_[i+1][j][k+1]);
                v.value = gridIsoValues_[i+1][j][k];
            } else {
                v.vector = ofVec3f(0.0,0.0,0.0);
                v.value = 1.0;
            }
     
            break;
        case 2:
            if(i < cGridResolution -2 && j != 0 && k < cGridResolution -2) {
                v.vector = ofVec3f(
                                   gridIsoValues_[i+1-1][j][k+1] - gridIsoValues_[i+1+1][j][k+1],
                                   gridIsoValues_[i+1][j-1][k+1] - gridIsoValues_[i+1][j+1][k+1],
                                   gridIsoValues_[i+1][j][k+1-1] - gridIsoValues_[i+1][j][k+1+1]);
                 v.value = gridIsoValues_[i+1][j][k+1];
            } else {
                v.vector = ofVec3f(0.0,0.0,0.0);
                v.value = 1.0;
            }
           
            break;
        case 3:
            if(i != 0 && j != 0 && k < cGridResolution -2) {
                v.vector = ofVec3f(
                                   gridIsoValues_[i-1][j][k+1] - gridIsoValues_[i+1][j][k+1],
                                   gridIsoValues_[i][j-1][k+1] - gridIsoValues_[i][j+1][k+1],
                                   gridIsoValues_[i][j][k+1-1] - gridIsoValues_[i][j][k+1+1]);
                  v.value = gridIsoValues_[i][j][k+1];
            } else {
                v.vector = ofVec3f(0.0,0.0,0.0);
                v.value = 1.0;
            }
          
            break;
        case 4:
            if(i != 0 && j < cGridResolution -2 && k != 0) {
                v.vector = ofVec3f(
                                   gridIsoValues_[i-1][j+1][k] - gridIsoValues_[i+1][j+1][k],
                                   gridIsoValues_[i][j+1-1][k] - gridIsoValues_[i][j+1+1][k],
                                   gridIsoValues_[i][j+1][k-1] - gridIsoValues_[i][j+1][k+1]);
                  v.value = gridIsoValues_[i][j+1][k];
            } else {
                v.vector = ofVec3f(0.0,0.0,0.0);
                v.value = 1.0;
            }
          
            break;
        case 5:
            if(i < cGridResolution -2 && j <cGridResolution -2 && k != 0) {
                v.vector = ofVec3f(
                                   gridIsoValues_[i+1-1][j+1][k] - gridIsoValues_[i+1+1][j+1][k],
                                   gridIsoValues_[i+1][j+1-1][k] - gridIsoValues_[i+1][j+1+1][k],
                                   gridIsoValues_[i+1][j+1][k-1] - gridIsoValues_[i+1][j+1][k+1]);
               v.value = gridIsoValues_[i+1][j+1][k];
            } else {
                v.vector = ofVec3f(0.0,0.0,0.0);
                v.value = 1.0;
            }
           
            break;
        case 6:
            if(i <cGridResolution -2 && j <cGridResolution -2 && k <cGridResolution -2) {
                v.vector = ofVec3f(
                                   gridIsoValues_[i+1-1][j+1][k+1] - gridIsoValues_[i+1+1][j+1][k+1],
                                   gridIsoValues_[i+1][j+1-1][k+1] - gridIsoValues_[i+1][j+1+1][k+1],
                                   gridIsoValues_[i+1][j+1][k+1-1] - gridIsoValues_[i+1][j+1][k+1+1]);
              v.value = gridIsoValues_[i+1][j+1][k+1];
            } else {
                v.vector = ofVec3f(0.0,0.0,0.0);
                v.value = 1.0;
            }
          
            break;
        case 7:
            if(i != 0 && j <cGridResolution -2 && k < cGridResolution -2) {
                v.vector = ofVec3f(
                                   gridIsoValues_[i-1][j+1][k+1] - gridIsoValues_[i+1][j+1][k+1],
                                   gridIsoValues_[i][j+1-1][k+1] - gridIsoValues_[i][j+1+1][k+1],
                                   gridIsoValues_[i][j+1][k+1-1] - gridIsoValues_[i][j+1][k+1+1]);
              v.value = gridIsoValues_[i][j+1][k+1];
            } else {
                v.vector = ofVec3f(0.0,0.0,0.0);
                v.value = 1.0;
            }
          
            break;
            
    }
}

//----------------------------------
void ofxKMarchingCubes::marchingCubes(int cubeX,int cubeY,int cubeZ,float threshold, bool needColor)
{
    int cubeindex = 0;
    
    int i = cubeX;
    int j = cubeY;
    int k = cubeZ;
    
	int idTable[12][2] = {
		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},
		{4, 5},
		{5, 6},
		{6, 7},
		{7, 4},
		{0, 4},
		{1, 5},
		{2, 6},
		{3, 7}
	};

    vec4 vv[8];
	ofColor c[8];
    
    for(int ind=0;ind<8;ind++) {
        getVec4(ind, i, j, k,vv[ind], c[ind]);
    }
    
    
    // check which vertices are inside the surface
    if(vv[0].value < threshold) cubeindex |= 1;
    if(vv[1].value < threshold) cubeindex |= 2;
    if(vv[2].value < threshold) cubeindex |= 4;
    if(vv[3].value < threshold) cubeindex |= 8;
    if(vv[4].value < threshold) cubeindex |= 16;
    if(vv[5].value < threshold) cubeindex |= 32;
    if(vv[6].value < threshold) cubeindex |= 64;
    if(vv[7].value < threshold) cubeindex |= 128;
    
   // ofLog() << cubeindex << endl;
    
    // cube is entirely out of the surface 
    if(edgeTable[cubeindex] == 0)
        return;
    
    /*
    // draw grid
    ofSetColor(100,100,100);
    ofLine(vv[0].vector,vv[1].vector);
    ofLine(vv[1].vector,vv[2].vector);
    ofLine(vv[2].vector,vv[3].vector);
    ofLine(vv[3].vector,vv[0].vector);
    ofLine(vv[4].vector,vv[5].vector);
    ofLine(vv[5].vector,vv[6].vector);
    ofLine(vv[6].vector,vv[7].vector);
    ofLine(vv[7].vector,vv[4].vector);
    ofLine(vv[5].vector,vv[1].vector);
    ofLine(vv[6].vector,vv[2].vector);
    ofLine(vv[7].vector,vv[3].vector);
    ofLine(vv[4].vector,vv[0].vector);
    */
    
    
    /* Find the vertices where the surface intersects the cube */
    
    // intersects with edge 0
	int val = 1;
	for (int i = 0; i < 12; i++)
	{
		if (edgeTable[cubeindex] & val)
		{
			if (needColor)
			{
				vertexInterpolation(
					threshold,
					vv[idTable[i][0]].vector, vv[idTable[i][1]].vector,
					vv[idTable[i][0]].value, vv[idTable[i][1]].value,
					c[idTable[i][0]], c[idTable[i][1]],
					vertList[i], colorList[i]
				);
			}
			else
			{
				vertexInterpolation(
					threshold, 
					vv[idTable[i][0]].vector, vv[idTable[i][1]].vector,
					vv[idTable[i][0]].value, vv[idTable[i][1]].value,
					vertList[i]
				);
			}

			//getGradient(idTable[i][0], i, j, k, gradients[idTable[i][0]]);
			//getGradient(idTable[i][1], i, j, k, gradients[idTable[i][1]]);
			//
			//vertexInterpolation(threshold, gradients[idTable[i][0]].vector, gradients[idTable[i][1]].vector
			//                    , gradients[idTable[i][0]].value, gradients[idTable[i][1]].value, gradList[i]);
		}
		val = val << 1;
	}
    /* create triangles */
    
  
    for(int ind=0;triTable[cubeindex][ind] != -1;ind+=3) {
        
		if (vertices.size() <= verticesIdx)
		{
			vertices.push_back(vertList[triTable[cubeindex][ind]]);
			vertices.push_back(vertList[triTable[cubeindex][ind + 1]]);
			vertices.push_back(vertList[triTable[cubeindex][ind + 2]]);

			//normals.push_back(gradList[triTable[cubeindex][ind]]);
			//normals.push_back(gradList[triTable[cubeindex][ind+1]]);
			//normals.push_back(gradList[triTable[cubeindex][ind+2]]);
			if (needColor)
			{
				colors.push_back(colorList[triTable[cubeindex][ind]]);
				colors.push_back(colorList[triTable[cubeindex][ind + 1]]);
				colors.push_back(colorList[triTable[cubeindex][ind + 2]]);
			}

		}
		else
		{
			vertices[verticesIdx] = vertList[triTable[cubeindex][ind]];
			vertices[verticesIdx+1] = vertList[triTable[cubeindex][ind + 1]];
			vertices[verticesIdx+2] = vertList[triTable[cubeindex][ind + 2]];

			if (needColor)
			{
				colors[verticesIdx] = colorList[triTable[cubeindex][ind]];
				colors[verticesIdx + 1] = colorList[triTable[cubeindex][ind + 1]];
				colors[verticesIdx + 2] = colorList[triTable[cubeindex][ind + 2]];
			}
		}
		verticesIdx += 3;
        numTriangles++;
    }
  
     
}

//----------------------------------
void ofxKMarchingCubes::vertexInterpolation(float threshold, 
                                            ofVec3f& p1, ofVec3f& p2, 
                                            float valp1, float valp2, 
                                            ofVec3f& vertex) 
{
    float mu;
    
  //  this is case where the resolution is too low anyway
    if (ABS(threshold-valp1) < 0.00001){
		vertex.set(p1.x, p1.y, p1.z);
		return;
	}
	if (ABS(threshold-valp2) < 0.00001){
		vertex.set(p2.x, p2.y, p2.z);
		return;
	}
	if (ABS(valp1-valp2) < 0.00001){
		vertex.set(p1.x, p1.x, p1.z);
		return;
	}
     
    
	mu = (threshold - valp1) / (valp2 - valp1);
    
	vertex.x = p1.x + mu * (p2.x - p1.x);
	vertex.y = p1.y + mu * (p2.y - p1.y);
	vertex.z = p1.z + mu * (p2.z - p1.z);    
}

//----------------------------------
void ofxKMarchingCubes::vertexInterpolation(float threshold, ofVec3f & p1, ofVec3f & p2, float valp1, float valp2, ofColor & c1, ofColor & c2, ofVec3f & vertex, ofColor & color)
{
	float mu;

	//  this is case where the resolution is too low anyway
	if (ABS(threshold - valp1) < 0.00001) {
		vertex.set(p1.x, p1.y, p1.z);
		color = c1;
		return;
	}
	if (ABS(threshold - valp2) < 0.00001) {
		vertex.set(p2.x, p2.y, p2.z);
		color = c2;
		return;
	}
	if (ABS(valp1 - valp2) < 0.00001) {
		vertex.set(p1.x, p1.x, p1.z);
		color = c1;
		return;
	}

	mu = (threshold - valp1) / (valp2 - valp1);

	vertex.x = p1.x + mu * (p2.x - p1.x);
	vertex.y = p1.y + mu * (p2.y - p1.y);
	vertex.z = p1.z + mu * (p2.z - p1.z);

	if (c1 == c2)
	{
		color = c1;
	}
	else
	{
		color.r = c1.r + mu * (c2.r - c1.r);
		color.g = c1.g + mu * (c2.g - c1.g);
		color.b = c1.b + mu * (c2.b - c1.b);
	}
}
