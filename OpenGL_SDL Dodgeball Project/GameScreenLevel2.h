#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include <SDL.h>
#include "GameScreen.h"
#include "object3DS.h"
#include "Pyramid.h"
#include "camera.h"
#include "GameScreenManager.h"
#include <vector>
#include "Ball.h"
#include "Cubes.h"
#include "Player.h"
#include "object3DS.h"
#include<sstream>
#include <time.h>

using namespace std;

class GameScreenLevel2 : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel2(GameScreenManager * gsm);
	~GameScreenLevel2();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void		SetLight();
	void		SetMaterial();

	void		ReadOBJ();

	void		GameOver();

	//--------------------------------------------------------------------------------------------------
private:

	// Player
	Player* m_Player;
	float playerRotation;

	// Floor
	Object3DS* m_Floor;
	float floorRotation;
	// Floor 2
	Object3DS* m_Floor2;

	float mCurrentTime;

	int health;
	int score;
	float framesPerSecond;

	Camera* camera;

	vector<Ball *> theBalls;
	vector<Cubes *> theCubes;

	GameScreenManager* screenManager;

	bool isPlayerAlive;

	time_t start = time(0);
	float timePlayed;

	stringstream stringStream1;
	stringstream stringStream2;

};


#endif //_GAMESCREENLEVEL2_H