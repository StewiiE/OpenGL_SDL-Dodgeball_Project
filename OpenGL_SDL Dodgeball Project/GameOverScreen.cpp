#include "GameOverScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenManager.h"
#include "GameScreen.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include <vector>
#include <iostream>


GameOverScreen::GameOverScreen(GameScreenManager * gsm) : GameScreen()
{
	mMenuItems.push_back("Main Menu");
	mMenuItems.push_back("Exit");
	if (mMenuItems.size() != 0)
	{
		selected = MENU_LEVEL1;
	}

	mInstructions.push_back("Game Over!");
	mInstructions.push_back("Use arrow keys to navigate menu");
	mInstructions.push_back("Enter to select");

	screenManager = gsm;
}


void GameOverScreen::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);

	int i;
	for (i = 0; i < mMenuItems.size(); i++)
	{
		if (i == selected)
		{
			glPushMatrix();
			glColor3f(1.0f, 0.4f, 0.0f);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glPopMatrix();
		}
		OutputLine(20, 40 - 10 * i, mMenuItems[i]);
	}
	for (int j = 0; j < mInstructions.size(); j++)
	{
		glColor3f(0.0, 0.0, 0.0);
		OutputLine(30, 100 - 10 * j - 10 * i, mInstructions[j]);
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GameOverScreen::Update(float deltaTime, SDL_Event e)
{
	HandleInput(e);
}

void GameOverScreen::HandleInput(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (selected > 0)
			{
				selected = selected - 1;
			}
			break;
		case SDLK_DOWN:
			if (selected < mMenuItems.size() - 1)
			{
				selected++;
			}
			break;

		case SDLK_RETURN:
			HandleSelectedItem();
			break;
		}
	}
}

void GameOverScreen::HandleSelectedItem()
{
	GameScreenManager* gsm;

	if (selected == MENU_LEVEL1)
	{
		screenManager->ChangeScreen(SCREEN_MENU);
	}
	if (selected == MENU_EXIT)
	{
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;
		SDL_PushEvent(&sdlevent);
	}
}
