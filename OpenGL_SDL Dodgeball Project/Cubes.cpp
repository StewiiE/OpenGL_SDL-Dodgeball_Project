#include "Cubes.h"
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "camera.h"
#include "Collision.h"
#include <math.h>
#include <iostream>
#include <MMSystem.h>
#include "Player.h"

using namespace::std;

Cubes::Cubes()
{
	// use random numbers to initialise the position, scale and velocity

	position.x = 5 * (float)rand() / (RAND_MAX)-5;
	position.y = 4.0f;  //10 * (float)rand() / (RAND_MAX + 10)-5;
	position.z = 3 * (float)rand() / (RAND_MAX)-1.5f;

	scale = 0.4f;  // (float)rand() / ((RAND_MAX * 2));


	velocity.x = 2000 * (float)rand() / ((RAND_MAX) * 1000) - .005;
	velocity.y = 500 * (float)rand() / ((RAND_MAX) * 1000) - .005;
	velocity.z = 0;

	acceleration = Vector3D(0.0f, -1.0f, 0.0f);

	boundingSphere = new Sphere(position, scale*1.2);

	cubesAttached = false;
}

void Cubes::Render()
{
	//if (boundingSphere->GetCollided()) 
	//	{
	//glColor3f(1.0f, 0.0f, 0.0f);
	//}
	//	else 
	//	{
	//glColor3f(0.0f, 1.0f, 0.0f);
	//	} 

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutSolidCube(scale);
	glColor3f(0.0f, 0.0f, 1.0f);
	//	glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);
	glPopMatrix();

}

void Cubes::Update(float deltaTime)
{
	if (!cubesAttached)
	{
		position += velocity * deltaTime + acceleration * (0.5 * deltaTime * deltaTime);
		velocity += acceleration * deltaTime;
		//velocity *= 0.999;

		boundingSphere->Update(position);

		if (boundingSphere != NULL)
		{

			boundingSphere->Update(position);


			boundingSphere->SetCollided(false);

			position += velocity * deltaTime + acceleration * (0.5 * deltaTime * deltaTime);
			velocity += (acceleration * deltaTime);

			if (position.y > 5 || position.y < 1)
				velocity.y *= -1.0f;


			// Moving Cubess if they fall off court
			if (position.x > 5 || position.x < -5)
			{
				position.x = 5 * (float)rand() / (RAND_MAX)-5;
				position.y = 4.0f;  //10 * (float)rand() / (RAND_MAX + 10)-5;
				position.z = 3 * (float)rand() / (RAND_MAX)-1.5f;

				velocity.x = 500 * (float)rand() / ((RAND_MAX) * 1000) - .005;
				velocity.y = 500 * (float)rand() / ((RAND_MAX) * 1000) - .005;
				velocity.z = 0;
			}


			if (position.z > 5 || position.z < -5)
			{
				position.x = 5 * (float)rand() / (RAND_MAX)-5;
				position.y = 4.0f;  //10 * (float)rand() / (RAND_MAX + 10)-5;
				position.z = 3 * (float)rand() / (RAND_MAX)-1.5f;

				velocity.x = 500 * (float)rand() / ((RAND_MAX) * 1000) - .005;
				velocity.y = 500 * (float)rand() / ((RAND_MAX) * 1000) - .005;
				velocity.z = 0;
			}

			if (position.y <= 1)
				playSound = true;

			if (playSound == true)
			{
				PlaySound(TEXT("Bounce.wav"), NULL, SND_LOOP | SND_ASYNC);
				playSound = false;
			}
			else
			{
				PlaySound(NULL, NULL, 0);
			}


		}
	}
	else
	{

		//position.x = (m_Player->GetPlayerPos().x - (1 * m_Player->GetCubess()));
		position.y = m_Player->GetPlayerPos().y;
		position.z = m_Player->GetPlayerPos().z;
	}
}

Sphere* Cubes::GetBoundingSphere()
{
	return boundingSphere;
}

void Cubes::DisableCollision()
{
	boundingSphere = NULL;
}

void Cubes::PlayerCollision(Player* player)
{
	m_Player = player;

	velocity = Vector3D(0.0f, 0.0f, 0.0f);
	acceleration = Vector3D(0.0f, 0.0f, 0.0f);

	//position.x = (player->GetPlayerPos().x - (1 * player->GetCubess()));
	position.y = player->GetPlayerPos().y;
	position.z = player->GetPlayerPos().z;

	cubesAttached = true;
}