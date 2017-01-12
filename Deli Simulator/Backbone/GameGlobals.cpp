#include "GameGlobals.h"

GameGlobals::GameGlobals (void)
{

}

GameGlobals::~GameGlobals (void)
{

}

GameState * GameGlobals::GetGameState(void)
{
	return &mGameState;
}

PlayerCharacter * GameGlobals::GetPlayer(void)
{
	return pPlayer;
}



void GameGlobals::SetPlayer(PlayerCharacter *player)
{
	pPlayer = player;
}