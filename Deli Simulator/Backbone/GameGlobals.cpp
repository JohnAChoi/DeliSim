#include "GameGlobals.h"
#include "GameMaster.h"

GameGlobals *pGameGlobals = nullptr;

GameGlobals::GameGlobals (void)
{
	pGameGlobals = this;
	mMenuState.mActiveMenu = false;
	mMenuState.mActiveTextbox = false;
}

GameGlobals::GameGlobals(GameMaster *gm): pGameMaster(gm)
{
	pGameGlobals = this;
	mMenuState.mActiveMenu = false;
	mMenuState.mActiveTextbox = false;
}

GameGlobals::~GameGlobals (void)
{

}

MenuState * GameGlobals::GetMenuState(void)
{
	return &mMenuState;
}

PlayerCharacter * GameGlobals::GetPlayer(void)
{
	return pGameMaster->pPlayer;
}

void GameGlobals::SetPlayer(PlayerCharacter *player)
{
	pGameMaster->pPlayer = player;
}