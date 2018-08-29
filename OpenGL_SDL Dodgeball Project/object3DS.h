#pragma once

#ifndef _OBJECT3DS_H_ 
#define _OBJECT3DS_H_ 

#include "Commons.h" 
#include <string> 
#include <SDL.h>
using std::string;

class Object3DS
{
public:

	Object3DS(Vector3D startPosition, string modelFileName, string texturePath);
	~Object3DS() {}

	void Update(float deltaTime, SDL_Event e);
	void Render();

	//Load 3ds file 
	void LoadModel();

	//Load texture for this model. 
	void LoadTexture(string texturePath);

private:
	Vector3D mPosition;
	float octopusRotation;

	char fileName[20];
	char textureName[20];

	obj_type object;

	Vector3D position = Vector3D();
	Vector3D forward = Vector3D();
	Vector3D up = Vector3D();
	Vector3D right = Vector3D();

	// horizontal angle : toward -Z
	float yaw = 3.14f;
	// vertical angle : 0, look at the horizon
	float pitch = 0.0f;

	bool movingRight = false;
	bool movingLeft = false;
	bool movingForward = false;
	bool movingBackward = false;
};
#endif //_OBJECT3DS_H_
