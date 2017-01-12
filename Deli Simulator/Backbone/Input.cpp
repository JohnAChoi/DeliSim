#include "Input.h"

//Declares an object that the entire project can access
Input Inputs;

Input::Input (void)
{
	//Figure this out later? Probably
}

Input::~Input (void)
{
	//This'll be obvious later
}

void Input::GetRawInput (void)
{
	SDL_PollEvent (&eInput);
}