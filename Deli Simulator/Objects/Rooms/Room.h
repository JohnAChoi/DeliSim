#ifndef _ROOM_H_
#define _ROOM_H_

#include "../Objects/BaseObject.h"
#include "engine/math/Vector2d.h"
#include "../Objects/Props/Prop.h"
#include <vector>
//#include "PlayerCharacter.h"

//Base class for the rooms in the game
class Room: public BaseObject
{
public:
	Room (void);
	Room (char* texture);
	Room (char* texture, int xsize, int ysize);
	~Room (void);

	void OnCreate	(void) override;
	void OnDestroy	(void) override;

	void Update		(void) override;
	void LateUpdate (void) override;
	void Draw		(void) override;

	int GetID (void);

	SDL_Rect GetDoor(int door_id);

protected:
	//Room ID number. Must be set for every room and should be unique
	int rID;

	//List of objects in the room
	//The first four objects should be the boundary walls for the room. 0 = top, 1 = right, 2 = bottom, 3 = left
	std::vector<Prop*> rPropList;
	
	//Entrances to the room. Players should spawn at them, obviously.
	std::vector<SDL_Rect> rDoors;

	//List of room (x), door (y) IDs that a room leads to
	std::vector<Engine::Vector2d> rNext;

	//List of exits from the room. Should be parallel to the rNext vector
	std::vector<SDL_Rect> rExits;
};


#endif