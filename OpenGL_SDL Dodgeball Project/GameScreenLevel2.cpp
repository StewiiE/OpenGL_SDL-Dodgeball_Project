#include "GameScreenLevel2.h"
#include "GameScreenManager.h"
#include "GameScreen.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Texture.h"
#include "object3DS.h"
#include "camera.h"
#include "objLoader.h"
#include <vector>
#include "Collision.h"
#include <iostream>
#include <MMSystem.h>
#include "Ball.h"
#include "Cubes.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel2::GameScreenLevel2(GameScreenManager * gsm) : GameScreen()
{
	// ---------------------------------- //
	// Commment for version control check //
	// ---------------------------------- //

	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

														//clear background colour.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	screenManager = gsm;

	isPlayerAlive = true;

	//Court 1
	m_Floor = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Court01.3ds", "Floor.raw");
	floorRotation = -90.0f;

	//Court 2
	m_Floor2 = new Object3DS(Vector3D(0.0f, 0.0f, 0.0f), "Court01.3ds", "Floor.raw");

	//Player
	m_Player = new Player(Vector3D(-4.5f, 0.0f, 1.5f), "ted.3ds", "Penguins.raw");
	playerRotation = 45.0f;



	health = 4;
	score = 30;

	//Balls
	for (int i = 0; i < 10; i++)
	{
		theBalls.push_back(new Ball());
	}

	/*//Cubes
	for (int i = 0; 1 < 10; i++)
	{
		theCubes.push_back(new Cubes());
	}*/


	camera = new Camera();
	camera->GetInstance();

	// enable lighting
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	srand(time(NULL));

	SetLight();
	SetMaterial();

	timePlayed = 0;
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel2::~GameScreenLevel2()
{

}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel2::SetLight()
{
	lighting light =
	{
		{ 10.8f, 10.8f, 10.8f, 1.0f },
		{ 11.0f, 11.0f, 11.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f }
	};
	// position of the light in homogeneous coordinates (x, y, z, w)
	// w should be 0 for directional lights, and 1 for spotlights
	float light_pos[] = { 0.0f, 5.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void GameScreenLevel2::SetMaterial()
{
	material material =
	{
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		0.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}

void GameScreenLevel2::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->Render();

	glEnable(GL_LIGHTING);
	glPushMatrix();

	//Floor 1
	glPushMatrix();
	glRotatef(floorRotation, 1, 0, 0);
	glTranslatef(-2.5f, 0, 0);
	m_Floor->Render();
	glPopMatrix();


	//Floor 2
	glPushMatrix();
	glRotatef(floorRotation, 1, 0, 0);
	glTranslatef(2.5f, 0, 0);
	m_Floor2->Render();
	glPopMatrix();


	//Player
	glPushMatrix();
	m_Player->Render();
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);

	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	OutputLine(5, 95, stringStream1.str());
	OutputLine(5, 92, stringStream2.str());
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	//Balls
	for (int i = 0; i < theBalls.size(); i++)
	{
		theBalls[i]->Render();
	}
	glPopMatrix();

	/*glPushMatrix();
	for (int i = 0; i < theCubes.size(); i++)
	{
		theCubes[i]->Render();
	}
	glPopMatrix(); */


}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	timePlayed = difftime(time(0), start);
	stringStream1.str("");
	stringStream1.clear();
	stringStream1 << "Time played: " << timePlayed << endl;
	stringStream2.str("");
	stringStream2.clear();
	stringStream2 << "Balls hit: " << m_Player->GetBalls() << endl;

	mCurrentTime += deltaTime;

	camera->Update(deltaTime, e);

	//Balls
	for (int i = 0; i < theBalls.size(); i++)
	{
		theBalls[i]->Update(deltaTime);
	}

	/*//Cubes
	for (int i = 0; i < theCubes.size(); i++)
	{
		theCubes[i]->Update(deltaTime);
	} */

	//Floor
	m_Floor->Update(deltaTime, e);

	//Floor2
	m_Floor2->Update(deltaTime, e);

	//Player
	m_Player->Update(deltaTime, e);

	// check for collisions

	if (isPlayerAlive == true)
	{
		if (theBalls.size() > 0)
		{
			for (int i = 0; i < theBalls.size(); i++)
			{
				if (theBalls[i]->GetBoundingSphere() != NULL)
				{
					if (Collision::SphereSphereCollision(m_Player->GetBoundingSphere(), theBalls[i]->GetBoundingSphere()))
					{
						cout << "Has collided" << endl;
						if (m_Player->GetBalls() <= 8)
						{
							theBalls[i]->DisableCollision();
							m_Player->AddBall();
							theBalls[i]->PlayerCollision(m_Player);
						}
						else
						{
							theBalls.clear();
							PlaySound(TEXT("Triumphant.wav"), NULL, SND_FILENAME | SND_ASYNC);
							screenManager->ChangeScreen(SCREEN_WINSCREEN);
							isPlayerAlive = false;
						}
					}
				}
			}
		}
	}


}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel2::GameOver()
{
	screenManager->ChangeScreen(SCREEN_GAMEOVER);
}