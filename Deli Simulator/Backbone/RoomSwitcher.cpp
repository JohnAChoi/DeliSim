#include "GameMaster.h"

//Include every room here. : |
#include "../Objects/Rooms/Test/TestRoom.h"
#include "../Objects/Rooms/Test/TestRoom2.h"

//Delete the current room and move to the next one
void GameMaster::TransitionToRoom (int next_room_id)
{
	//This should never be null, but double check anyway
	if (pCurrentRoom)
		gamestate->DeleteObject(pCurrentRoom);

	//Create the next room
	switch (next_room_id)
	{
	case 0:
		pCurrentRoom = (Room*)gamestate->CreateObject<TestRoom>();
		break;
	case 1:
		pCurrentRoom = (Room*)gamestate->CreateObject<TestRoom2>();
		break;
	default:
		std::cout << "Error in creating room with ID " << next_room_id << std::endl;
		break;
	}
}