#include "GameMaster.h"

GameMaster* SceneChanger = NULL;

//Constructor. Defaults to the game starting in the main menu and in RPG mode.
GameMaster::GameMaster (Engine::GameState* gs, int gamemode = 0, int startroom = 0):
	gamestate(gs), iGameMode (gamemode)//, iEngineMode (enginemode)
{
	SceneChanger = this;
	TransitionToRoom(startroom);
	SpawnPlayer();
}

//Destructor. Is really lame because it just sets things to 0.
GameMaster::~GameMaster (void)
{
	iGameMode = 0;
	//iEngineMode = 0;
}

//In case this object gets created by something. Shouldn't ever happen, though.
/*void GameMaster::OnCreate (int gamemode = 0, int enginemode = 0)
{
	iGameMode = gamemode;
	iEngineMode = enginemode;
}

//In case this object gets destroyed by something. Shouldn't ever happen, though. This and the previous one may get taken out
void GameMaster::OnDestroy (void)
{
	iGameMode = 0;
	iEngineMode = 0;
}

//I'll find a use for these later?
void GameMaster::Update	(void)
{}

//Otherwise, just take them all out
void GameMaster::LateUpdate	(void)
{}

//
void GameMaster::Draw (void)
{}
*/
//Getter for Game Mode. Easy
int	GameMaster::GetGameMode	(void)
{
	return iGameMode;
}


bool GameMaster::SetGameMode (int next_mode)
{
	iGameMode = next_mode;
	//Remember to go change other stuff!
	return true;
}

//Getter for Engine Mode. Easy
/*int	GameMaster::GetEngineMode (void)
{
	return iEngineMode;
}

bool GameMaster::SetEngineMode (int next_mode)
{
	iEngineMode = next_mode;
	//Remember to go change other stuff when the engine grows!
	return true;
}*/

//Function to spawn player at default door
void GameMaster::SpawnPlayer (void)
{
	pPlayer = (PlayerCharacter*)gamestate->CreateObject<PlayerCharacter>();
	SDL_Rect door = pCurrentRoom->GetDoor(0);
	pPlayer->SetPosition(door);
}

//Function to spawn player at any door in a room
void GameMaster::SpawnPlayer (int door_id)
{
	pPlayer = (PlayerCharacter*)gamestate->CreateObject<PlayerCharacter>();
	SDL_Rect door = pCurrentRoom->GetDoor(door_id);
	pPlayer->SetPosition(door);
}

//Transition to a specific room in a door.
//This function will assume the player has already been created for now.
void GameMaster::TransitionToDoor (int next_room_id, int door_id)
{
	//Move to the next room
	TransitionToRoom(next_room_id);
	//Get the coordinates the player should spawn at in the next room
	SDL_Rect door = pCurrentRoom->GetDoor(door_id);
	pPlayer->SetPosition(door);
}