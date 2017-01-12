#include "RenderTest.h"
#include <iostream>

RenderTest* ren;

RenderTest::RenderTest (void)
{
	window = SDL_CreateWindow("Resolution Test",0,0, 1366, 768,SDL_WINDOW_SHOWN);
	if (window == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	}

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == nullptr){
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	}

	iScreenHeight = 768;
	iScreenWidth = 1366;
}

RenderTest::~RenderTest (void)
{
	if (window)
		SDL_DestroyWindow (window);
	window = NULL;

	if (render)
		SDL_DestroyRenderer (render);
	render = NULL;
}