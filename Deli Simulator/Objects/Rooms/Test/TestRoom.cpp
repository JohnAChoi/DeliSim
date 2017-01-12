#include "TestRoom.h"
#include "../Objects/Props/Wall.h"
#include "../Objects/Characters/PlayerCharacter.h"
#include "../Backbone/GameMaster.h"

TestRoom::TestRoom (void): Room("./res/fullres_testimage.png", 1366, 768) 
{
	rID = 0;
	//Walls are created in the base Room class.
	//rSize.x = 1366;
	//rSize.y = 768;
/*	rPropList.push_back ((Prop*) new Wall ( 0, 0, rSize.x, 1, "./res/red_block.png"));
	rPropList.push_back ((Prop*) new Wall ( rSize.x - 1, 0, 1, rSize.y, "./res/green_block.png"));
	rPropList.push_back ((Prop*) new Wall ( 0, rSize.y - 1, rSize.x, 1, "./res/blue_block.png"));
	rPropList.push_back ((Prop*) new Wall (0, 0, 1, rSize.y, "./res/purple_block.png"));*/
	rPropList.push_back ((Prop*) new Wall ( 200, 200, 300, 50, "./res/pink_block.png"));

	SDL_Rect door; 
	door.x = 64;
	door.y = 64;
	rDoors.push_back (door);

	SDL_Rect door2;
	door2.x = 1275;
	door2.y = 625;
	rDoors.push_back (door2);

	Engine::Vector2d next;
	next.x = 1;
	next.y = 0;
	rNext.push_back (next);

	SDL_Rect exit;
	exit.x = 1295;
	exit.y = 635;
	exit.h = 128;
	exit.w = 64;
	rExits.push_back(exit);
}
	
TestRoom::TestRoom (SDL_Rect pos) {}

TestRoom::TestRoom (int height, int width) {}

//Base Room class deletes all props
TestRoom::~TestRoom (void) {}

void TestRoom::OnCreate	(void) {}
	
void TestRoom::OnDestroy	(void) {}

void TestRoom::Update (void) 
{
	Room::Update();
	/*SDL_Rect* current = Player->GetPosition();
	for (int i = 0; i < rExits.size(); i++)
	{
		if (current->x >= rExits[i].x && current->x <= (rExits[i].x + rExits[i].w))
			if (current->y >= rExits[i].y && current->y <= (rExits[i].y + rExits[i].h))
				SceneChanger->TransitionToDoor(rNext[i].x, rNext[i].y);
	}*/
}

void TestRoom::LateUpdate (void) {}
	
//void TestRoom::Draw (void) {}