#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"
#include "WinScreen.h"

//--------------------------------------------------------------------------------------------------

GameScreenManager::GameScreenManager(SCREENS startScreen)
{
	mCurrentScreen = NULL;

	//Ensure the first screen is set up.
	ChangeScreen(startScreen);
}

//--------------------------------------------------------------------------------------------------

GameScreenManager::~GameScreenManager()
{
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	if(mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	MenuScreen* menuScreen;
	GameScreenLevel1* level1Screen;
	GameScreenLevel2* level2Screen;
	GameOverScreen* gameOverScreen;
	WinScreen* winScreen;

	//Initialise the new screen.
	switch(newScreen)
	{
		case SCREEN_INTRO:
		break;

		case SCREEN_MENU:
			menuScreen = new MenuScreen(this);
			mCurrentScreen = (GameScreen*)menuScreen;
			menuScreen = NULL;
		break;

		case SCREEN_LEVEL1:
			level1Screen = new GameScreenLevel1(this);
			mCurrentScreen = (GameScreen*)level1Screen;
			level1Screen = NULL;
		break;

		case SCREEN_LEVEL2:
			level2Screen = new GameScreenLevel2(this);
			mCurrentScreen = (GameScreen*)level2Screen;
			level2Screen = NULL;
			break;
		
		case SCREEN_GAMEOVER:
			gameOverScreen = new GameOverScreen(this);
			mCurrentScreen = (GameScreen*)gameOverScreen;
			gameOverScreen = NULL;
		break;

		case SCREEN_WINSCREEN:
			winScreen = new WinScreen(this);
			mCurrentScreen = (GameScreen*)winScreen;
			winScreen = NULL;
			break;
		
		case SCREEN_HIGHSCORES:
		break;
		
		default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------