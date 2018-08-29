#include "Player.h" 
#include "3dsLoader.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenManager.h"
#include "GameScreen.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "camera.h"
#include "Collision.h"
#include <math.h>
#include <iostream>
#include "Texture.h"

//--------------------------------------------------------------------------------------------------
static float moveSpeed = 3.0f;

using namespace::std;


Player::Player(Vector3D startPosition, string modelFileName, string texturePath)
{
	//start position. 
	mPosition = startPosition;

	//3ds file to load. 
	std::strcpy(fileName, modelFileName.c_str());
	LoadModel();

	LoadTexture(texturePath);

	boundingSphere = new Sphere(mPosition, 0.8f);

	health = 4;

	ballCount = 0;
}
//--------------------------------------------------------------------------------------------------

void Player::LoadModel()
{
	if (fileName[0] != '-')
		Load3DS(&object, fileName);
}
//--------------------------------------------------------------------------------------------------

void Player::LoadTexture(string texturePath)
{
	Texture2D* texture = new Texture2D();
	texture->Load(texturePath.c_str(), 512, 512);
	object.id_texture = texture->GetID();

	glBindTexture(GL_TEXTURE_2D, texture->GetID());

	glEnable(GL_TEXTURE_2D);

	//set some paramaters so it renders correctly
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
//--------------------------------------------------------------------------------------------------

void Player::Update(float deltaTime, SDL_Event e)
{
	boundingSphere->SetCollided(false);

	//cout << "X: " << mPosition.x << " Y: " << mPosition.y << " Z: " << mPosition.z << endl;

	// Forward Vector: Spherical coordinates to Cartesian coordinates
	// conversion(also known as the ‘look’ direction)
	forward = Vector3D(
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw));

	// Right vector
	right = Vector3D(
		sin(yaw - 3.14f / 2.0f),
		0,
		cos(yaw - 3.14f / 2.0f));

	// Up vector : perpendicular to both forward and right, calculate using
	// the cross product
	up = Vector3D((right.y*forward.z) - (right.z*forward.y),
		(right.z*forward.x) - (right.x*forward.z),
		(right.x*forward.y) - (right.y*forward.x));

	//Event Handler.
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			//move forwards
			movingForward = true;
			movingBackward = false;
			break;

		case SDLK_s:
			//add move backwards code using the forward vector
			movingBackward = true;
			movingForward = false;
			break;

		case SDLK_d:
			//add strafe right code using the right vector
			movingRight = true;
			movingLeft = false;
			break;

		case SDLK_a:
			//add strafe left code using the right vector
			movingRight = false;
			movingLeft = true;
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			movingForward = false;
			break;

		case SDLK_s:
			movingBackward = false;
			break;

		case SDLK_d:
			movingRight = false;
			break;

		case SDLK_a:
			movingLeft = false;
			break;
		}
	default:
		break;
	}

	if (movingForward == true)
	{
		mPosition += (forward * moveSpeed) * deltaTime;
	}
	if (movingBackward == true)
	{
		mPosition -= (forward * moveSpeed) * deltaTime;
	}
	if (movingRight == true)
	{
		mPosition += (right * moveSpeed) * deltaTime;
	}
	if (movingLeft == true)
	{
		mPosition -= (right * moveSpeed) * deltaTime;
	}

	boundingSphere->Update(mPosition);
}
//-------------------------------------------------------------------------------------------------- 

void Player::Render()
{
	glPushMatrix();
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);

	glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 

	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles) 

	for (int l_index = 0; l_index < object.triangles_qty; l_index++)
	{
		//-----------------FIRST VERTEX ----------------// 
		// Texture coordinates of the first vertex 
		glTexCoord2f(object.texcoord[object.triangle[l_index].a].u,
			object.texcoord[object.triangle[l_index].a].v);
		// Coordinates of the first vertex 
		glVertex3f(object.vertex[object.triangle[l_index].a].x,
			object.vertex[object.triangle[l_index].a].y,
			object.vertex[object.triangle[l_index].a].z);
		//Vertex definition

		//-----------------SECOND VERTEX ---------------//
		// Texture coordinates of the second vertex 
		glTexCoord2f(object.texcoord[object.triangle[l_index].b].u,
			object.texcoord[object.triangle[l_index].b].v);
		// Coordinates of the second vertex 
		glVertex3f(object.vertex[object.triangle[l_index].b].x,
			object.vertex[object.triangle[l_index].b].y,
			object.vertex[object.triangle[l_index].b].z);

		//-----------------THIRD VERTEX -----------------
		// Texture coordinates of the third vertex 
		glTexCoord2f(object.texcoord[object.triangle[l_index].c].u,
			object.texcoord[object.triangle[l_index].c].v);
		// Coordinates of the Third vertex 
		glVertex3f(object.vertex[object.triangle[l_index].c].x,
			object.vertex[object.triangle[l_index].c].y,
			object.vertex[object.triangle[l_index].c].z);
	}

	if (boundingSphere->GetCollided())
	{
	}
	else
	{
	} 

	glEnd();
	glPopMatrix();
}
//--------------------------------------------------------------------------------------------------

Sphere * Player::GetBoundingSphere()
{
	return boundingSphere;
}

int Player::GetBalls()
{
	return ballCount;
}

int Player::AddBall()
{
	cout << ballCount << endl;
	return ballCount++;
}