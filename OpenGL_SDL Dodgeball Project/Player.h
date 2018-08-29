#pragma once

#ifndef _PLAYER_H_ 
#define _PLAYER_H_ 

#include "Commons.h" 
#include <string> 
#include <SDL.h>
#include "GameScreenManager.h"
using std::string;

class Sphere;
class Player
{
public:

	Player(Vector3D startPosition, string modelFileName, string texturePath);
	~Player() {}

	void Update(float deltaTime, SDL_Event e);
	void Render();

	//Load 3ds file 
	void LoadModel();

	//Load texture for this model. 
	void LoadTexture(string texturePath);

	Sphere * GetBoundingSphere();

	Vector3D GetPlayerPos() { return mPosition; }

	int GetBalls();
	int AddBall();

private:
	Vector3D mPosition;

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

	float scale;
	Sphere * boundingSphere;

	int health;

	int ballCount;
};
#endif //_PLAYER_H_
