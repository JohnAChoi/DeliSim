#include "BaseObject.h"
#include "../Renderer/RenderTest.h"
#include <SDL_image.h>

//Constructors are called right when object is created -> DUH
BaseObject::BaseObject (void):
	Behavior()
{
	rPosition.x = 0;
	rPosition.y = 0;
	rPosition.h = ren->iScreenHeight;
	rPosition.w = ren->iScreenWidth;
	tObjTex = NULL;
}

BaseObject::BaseObject (SDL_Rect start_pos, char* texture_name):
	Behavior(), rPosition(start_pos)
{
	tObjTex = LoadTexture (texture_name);
}

BaseObject::BaseObject (char* texture_name)
{
	tObjTex = LoadTexture (texture_name);
}

BaseObject::~BaseObject (void)
{
	rPosition.x = 0;
	rPosition.y = 0;
	rPosition.h = 0;
	rPosition.w = 0;
	if (tObjTex)
	{
		SDL_DestroyTexture (tObjTex);
		//delete tObjTex;
	}
	tObjTex = NULL;
}

//Called the frame AFTER an object is created. Some weird stuff with memory in C++
//Maybe I won't end up needing or it will be absolutely vital? Who knows?
void BaseObject::OnCreate (void) {}

//Called the frame BEFORE the destructor is called. Probably related to the
//Constructor/OnCreate thing. Get details when necessary.
void BaseObject::OnDestroy (void) {}

void BaseObject::Update	(void) 
{ 
	//Stuff should happen here 
}

void BaseObject::LateUpdate (void)
{
	//Maybe this will stay blank. Who knows?
}

void BaseObject::Draw (void)
{
	//Figure this out soon
	SDL_RenderCopy ((ren)->render, tObjTex, NULL, &rPosition);
}

SDL_Rect* BaseObject::GetPosition (void)
{
	return &rPosition;
}

void BaseObject::SetPosition (SDL_Rect new_pos)
{
	rPosition.x = new_pos.x;
	rPosition.y = new_pos.y;
	//rPosition.h = new_pos.h;
	//rPosition.w = new_pos.w;
	//Not sure about height + width, but put it here anyway.
}

SDL_Texture* BaseObject::LoadTexture (char* texname)
{
	SDL_Surface *bmp = IMG_Load(texname);
	if (bmp == nullptr){
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface((ren)->render, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr){
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
	}
	
	return tex;
}