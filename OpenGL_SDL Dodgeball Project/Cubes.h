#pragma once
#include "Commons.h"
#include "Player.h"
class Sphere;
class Cubes
{

public:

	Cubes();
	~Cubes() { };
	void Update(float deltaTime);
	void Render();
	Sphere * GetBoundingSphere();
	void DisableCollision();
	void PlayerCollision(Player* player);

private:

	Vector3D	position;
	float		scale;
	Vector3D	velocity;
	Vector3D	acceleration;
	Sphere *	boundingSphere;
	bool		playSound;
	Player*		m_Player;
	bool		cubesAttached;

};