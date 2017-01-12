#include "MovementKeyboard.h"
#include "SDL_keyboard.h"


MovementKeyboard::MovementKeyboard (void) {}

MovementKeyboard::~MovementKeyboard (void) 
{
	//Don't have to worry about freeing this memory up since it's handled by SDL
	kbState = NULL;
}

//This function takes a pointer to a b2Vec2 to return the velocity
//The int returned is the sprite index (for now)
//Ideally, pass in a b2Vec2 with (0,0)
int MovementKeyboard::GetMove(b2Vec2 *velocity)
{
	kbState = SDL_GetKeyboardState(NULL);
	int spr_index = 0;

	//Move the player
	//Later on, use an internal mask to allow for custom keyboard configs
	//Also, uses the hardware scan code, so keyboard layout doesn't matter.
	//Abstract to movement class
	if (kbState[SDL_SCANCODE_W])
	{
		spr_index = 1;
		velocity->y -= 1.0;
	}

	if (kbState[SDL_SCANCODE_S])
	{
		spr_index = 0;
		velocity->y += 1.0;
	}

	if (kbState[SDL_SCANCODE_A])
	{
		spr_index = 3;
		velocity->x -= 1.0;
	}

	if (kbState[SDL_SCANCODE_D])
	{
		spr_index = 2;
		velocity->x += 1.0;
	}

	//GOTTA GO FAST -> EVEN FASTER
	if (kbState[SDL_SCANCODE_LSHIFT])
		(*velocity) *= 4;

	return spr_index;
}