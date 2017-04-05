#ifndef _GAME_GLOBALS_H_
#define _GAME_GLOBALS_H_

#include "engine/GameState.h"

class PlayerCharacter;
class RenderTest;
class GameMaster;

struct MenuState
{
	bool mActiveTextbox;
	bool mActiveMenu;
};

//This class should handle access to all global variables and classes in the game
//This should be helpful in debugging. Or maybe it'll just add another layer of stupidity.
class GameGlobals 
{
public:
		GameGlobals(void);
		GameGlobals (GameMaster *gm);
		~GameGlobals(void);

		//Getters
		MenuState * GetMenuState(void);
		PlayerCharacter * GetPlayer(void);

		//Setters
		void SetPlayer (PlayerCharacter *player);

private:
	MenuState mMenuState;
	//Engine::GameState* gamestate; Use from GameMaster, I think
	GameMaster *pGameMaster;
	//PlayerCharacter *pPlayer;
	RenderTest *pRenderer;
};
extern GameGlobals* pGameGlobals;
#endif
