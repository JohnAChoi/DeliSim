#include "TestRoom2.h"
#include "../Objects/Props/Wall.h"
#include "../Objects/Characters/PlayerCharacter.h"
#include "../Backbone/GameMaster.h"

TestRoom2::TestRoom2 (void): Room("./res/Test2.png", 1366, 768) 
{
	rID = 1;
	//Walls are created in the base Room class.
	//rSize.x = 1366;
	//rSize.y = 768;
/*	rPropList.push_back ((Prop*) new Wall ( 0, 0, rSize.x, 1, "./res/red_block.png"));
	rPropList.push_back ((Prop*) new Wall ( rSize.x - 1, 0, 1, rSize.y, "./res/green_block.png"));
	rPropList.push_back ((Prop*) new Wall ( 0, rSize.y - 1, rSize.x, 1, "./res/blue_block.png"));
	rPropList.push_back ((Prop*) new Wall (0, 0, 1, rSize.y, "./res/purple_block.png"));*/
	//rPropList.push_back ((Prop*) new Wall ( 200, 200, 300, 50, "./res/pink_block.png"));

	SDL_Rect door; 
	door.x = 70;
	door.y = 630;
	rDoors.push_back (door);

	Engine::Vector2d next;
	next.x = 0;
	next.y = 1;
	rNext.push_back (next);

	SDL_Rect exit;
	exit.x = 1;
	exit.y = 630;
	exit.h = 128;
	exit.w = 32;
	rExits.push_back(exit);
}
	
TestRoom2::TestRoom2 (SDL_Rect pos) {}

TestRoom2::TestRoom2(int height, int width) {}

//Base Room class deletes all props
TestRoom2::~TestRoom2 (void) 
{
	Room::~Room();
}

void TestRoom2::OnCreate	(void) {}
	
void TestRoom2::OnDestroy	(void) {}

void TestRoom2::Update (void) 
{
	Room::Update();
}

void TestRoom2::LateUpdate (void) {}
	
//void TestRoom2::Draw (void) {}