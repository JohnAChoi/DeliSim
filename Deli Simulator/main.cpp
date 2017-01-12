#include "math/Vector3d.h"
#include "engine/Behavior.h"
#include "engine/GameState.h"
#include "Objects/testobject.h"
//#include "WorldObject.h" 
#include "Objects/Rooms/Test/TestRoom.h"
#include "Objects/Actor.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Backbone/Input.h"
#include "Renderer/RenderTest.h"
#include "Objects/Characters/PlayerCharacter.h"
#include "Box2D/Box2D.h"
#include "Physics.h"
#include "Backbone/GameMaster.h"

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ( IMG_Init(IMG_INIT_PNG) == 0)
	{
		std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
		return 1;
	}

	if (TTF_Init () == -1)
	{
		std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
		return 1;
	}

	ren = new RenderTest();
	
	Engine::GameState gamestate;
	Physics physicsengine;
	bool quit = false;
	GameMaster scene (&gamestate, 0, 0);

	//new TestObject;
	//gamestate.CreateObject<TestObject>();
	//gamestate.CreateObject<TestRoom>();
	//gamestate.CreateObject<PlayerCharacter>();

	while ( !quit ) {
		Inputs.GetRawInput();
		if (Inputs.eInput.type == SDL_QUIT || Inputs.eInput.key.keysym.sym == SDLK_ESCAPE)
			quit = true;

		physicsengine.Step();
		gamestate.Step();
		gamestate.Draw();
	}
	
	if (ren)
		delete ren;
	ren = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	// gamestate deleted down here
	return 0;
}