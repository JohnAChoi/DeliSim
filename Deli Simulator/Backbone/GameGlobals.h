#ifndef _GAME_GLOBALS_H_
#define _GAME_GLOBALS_H_

class PlayerCharacter;
class RenderTest;

struct GameState
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
		~GameGlobals(void);

		//Getters
		GameState * GetGameState(void);
		PlayerCharacter * GetPlayer(void);

		//Setters
		void SetPlayer (PlayerCharacter *player);

private:
	GameState mGameState;
	PlayerCharacter *pPlayer;
	RenderTest *pRenderer;
};
extern GameState * pGameState;
#endif
