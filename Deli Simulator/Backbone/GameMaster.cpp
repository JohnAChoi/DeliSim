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

//Spawn player at the default door to the room
void GameMaster::SpawnPlayer (void)
{
	pPlayer = (PlayerCharacter*)gamestate->CreateObject<PlayerCharacter>();
	SDL_Rect door = pCurrentRoom->GetDoor(0);
	pPlayer->SetPosition(door);
}

//Spawn player a specific door in a room
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