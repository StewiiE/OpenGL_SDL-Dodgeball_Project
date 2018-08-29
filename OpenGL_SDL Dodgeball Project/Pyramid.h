#ifndef _PYRAMID_H
#define _PYRAMID_H

#include <Windows.h> //Required for OpenGL on Windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL Utilities
#include "Commons.h"

class Pyramid
{
private:
	Vertex3D * indexedVertices;
	short * indices;

	int numVertices;
	int indexCount;

	bool Load(char* path);
	void DrawTriangle(short a, short b, short c);

	int numNormals;
	Vector3D * normals;

public:
	Pyramid(void);
	~Pyramid(void);

	void Draw(void);
	void Update(void);
};

#endif