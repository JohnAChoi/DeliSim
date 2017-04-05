#ifndef _GAME_MASTER_H_
#define _GAME_MASTER_H_

#include "engine/GameState.h"
#include "../Objects/Rooms/Room.h"
#include "../Objects/Characters/PlayerCharacter.h"

class GameGlobals;

//This should probably be called "Scene Changer"
class GameMaster//: public Engine::Behavior
{
	friend class GameGlobals;
public:
	enum GameModes 
	{
		MAINMENU	=	0,
		INGAME		=	1,
		CUTSCENE	=	2,
		PAUSED
	};
	
	/*enum EngineModes
	{
		RPG			=	0,
		BEATEMUP	=	1,
		PLATFORMER	=	2,
		VERTSHOOTER	=	3,
		HORSHOOTER	=	4,
		SPECIAL
	};*/

public:
	
	GameMaster (Engine::GameState* gs, int gamemode, int startroom);
	~GameMaster (void);

	//Getters because it could be handy
	int		GetGameMode		(void);
	//int		GetEngineMode	(void);

	//Setters because they will be necessary
	bool	SetGameMode		(int next_mode);
	//bool	SetEngineMode	(int next_mode);

	//Functions for rooms
	//Automatically spawns the player at the default door
	void TransitionToRoom (int next_room_id);

	//Spawn the player at a specific door in a room
	void TransitionToDoor (int next_room_id, int door_id);

	//Functions for the player
	void SpawnPlayer (void);
	void SpawnPlayer (int door_id);
	//void SpawnPlayer (int x_pos, int y_pos);

private:
	int iGameMode;
	Engine::GameState* gamestate;
	Room* pCurrentRoom;
	PlayerCharacter* pPlayer;
	//int iEngineMode;
};
extern GameMaster* SceneChanger;

#endif