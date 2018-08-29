#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "object3DS.h"
#include "Pyramid.h"
#include "camera.h"
#include "Player.h"
#include <sstream>
#include <string.h>
#include "Ball.h"
#include "GameScreenManager.h"
#include <vector>
#include<time.h>

using namespace std;

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1(GameScreenManager * gsm);
	~GameScreenLevel1();

	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void		SetLight();
	void		SetMaterial();

	void		ReadOBJ();

	void		GameOver();

//--------------------------------------------------------------------------------------------------
private:
	
	float mCurrentTime;
	Pyramid* pyramid;
	float pyramidRotation;

	Object3DS* m_Court1;
	Object3DS* m_Court2;
	float courtRotation;

	Player* m_Player;
	float playerRotation;

	stringstream ss;
	stringstream controlsText;
	int health;
	int score;
	float framesPerSecond;

	Camera* camera;

	vector<Ball *> theBalls;

	GameScreenManager* screenManager;

	bool isPlayerAlive;

	time_t start = time(0);
	float timePlayed;

	stringstream stringStream1;
	stringstream stringStream2;
};


#endif //_GAMESCREENLEVEL1_H