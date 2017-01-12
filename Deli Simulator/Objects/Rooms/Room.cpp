#include "Room.h"
#include "../Props/Wall.h"
#include "../Characters/PlayerCharacter.h"
#include "../Backbone/GameMaster.h"
//#include "RenderTest.h"

	Room::Room (void) : BaseObject()
	{
	}

	Room::Room (char* texture) : BaseObject(texture)
	{
		//Declare the size, rPosition, in inheriting classes
		//To make sure that the right size is created.
		//Declare the ID of the room as well.
		//Doors are a 2D vector with x being the ID of the next room to create
		//Y is the door to land on
		//rExits defines the box that the player has to enter to go to the next room
		//rExits and rNext should be parallel arrays, so rExits[i] leads to rNext[i]
	}
	
	Room::Room (char* texture, int xsize, int ysize): BaseObject(texture)
	{
		rPosition.w = xsize;
		rPosition.h = ysize;
		rPropList.push_back ((Prop*) new Wall ( 0, 0, rPosition.w, 1, "./res/red_block.png"));
		rPropList.push_back ((Prop*) new Wall ( rPosition.w - 1, 0, 1, rPosition.h, "./res/green_block.png"));
		rPropList.push_back ((Prop*) new Wall ( 0, rPosition.h - 1, rPosition.w, 1, "./res/blue_block.png"));
		rPropList.push_back ((Prop*) new Wall (0, 0, 1, rPosition.h, "./res/purple_block.png"));
		
		//Arbitrary render depth value for backgrounds
		m_render_depth = 10;
	}

	Room::~Room (void)
	{
		if (!rPropList.empty()) //It should almost never be empty, but never hurts to check
		{
			for (auto t_Prop = rPropList.begin(); t_Prop < rPropList.end(); t_Prop++)
				delete *t_Prop;
			rPropList.clear();
		}
	}

	void Room::OnCreate	(void) {}
	void Room::OnDestroy (void){}

	void Room::Update (void)
	{
		//Check if the player has entered a door
		//If he has, changes rooms
		SDL_Rect* current = Player->GetPosition();
		for (int i = 0; i < rExits.size(); i++)
		{
			if (current->x >= rExits[i].x && current->x <= (rExits[i].x + rExits[i].w))
				if (current->y >= rExits[i].y && current->y <= (rExits[i].y + rExits[i].h))
					SceneChanger->TransitionToDoor(rNext[i].x, rNext[i].y);
		}
	}
	void Room::LateUpdate (void){}
	
	void Room::Draw	(void) 
	{
		SDL_RenderCopy ((ren)->render, tObjTex, NULL, NULL);
	}

	int Room::GetID (void)
	{
		return rID;
	}

	/*
	Getter for room's props
	Way to construct all of them from here?
	*/

	SDL_Rect Room::GetDoor (int door_id)
	{
		if (door_id < rDoors.size() && door_id > -1)
			return rDoors[door_id];
		else
		{
			std::cout << "Room ID: " << rID << "\nError in door ID: " << door_id << "\nNumber of Doors in room: " << rDoors.size() 
				<< "\nReturning default door." << std::endl;

			return rDoors[0];
		}
	}