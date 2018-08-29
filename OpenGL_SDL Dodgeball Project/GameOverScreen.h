#ifndef GAMEOVER_SCREEN_H
#define GAMEOVER_SCREEN_H
#include <vector>
#include <string>
#include "GameScreen.h"
#include "GameScreenManager.h"
using namespace std;

#define MENU_NONE -1
#define MENU_LEVEL1 0
#define MENU_EXIT   1 

class GameOverScreen : public GameScreen
{
public:
	GameOverScreen(GameScreenManager * gsm);
	~GameOverScreen() {};
	void Render();
	void Update(float deltaTime, SDL_Event e);

protected:
	void HandleInput(SDL_Event e);
	vector<string> mInstructions;
	vector<string> mMenuItems;
	GameScreenManager* screenManager;

private:
	int selected = MENU_NONE;
	void HandleSelectedItem();
};
#endif
