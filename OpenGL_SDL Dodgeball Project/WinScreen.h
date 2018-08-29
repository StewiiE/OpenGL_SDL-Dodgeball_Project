#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H
#include <vector>
#include <string>
#include "GameScreen.h"
#include "GameScreenManager.h"
using namespace std;

#define MENU_NONE -1
#define MENU_MENU	0
#define MENU_LEVEL1 1
#define MENU_EXIT   2 

class WinScreen : public GameScreen
{
public:
	WinScreen(GameScreenManager * gsm);
	~WinScreen() {};
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
