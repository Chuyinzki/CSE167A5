#pragma once

#include <cstdio>
#include <stdio.h>
#include <vector>
#include "Vector3.h"
#include <GL/glut.h>
#include "Matrix4.h"
#include <string>
#include <vector>

#include <sstream>
#include <fstream>

class FileObj2
{
protected:

	Matrix4 model2world;

	vector <float> vertex;
	vector <float> vertexColors;
	vector <float> vertexNormals;

	vector <int> facesv;
	vector <int> facesn;

public:
	FileObj2(char *);
	~FileObj2();

	void parse(char *);
	void draw();
	Matrix4& getMatrix();
	void findMax();

	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float adjustX, adjustY, adjustZ;
};