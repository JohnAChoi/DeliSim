#ifndef _RENDER_TEST_H_
#define _RENDER_TEST_H_

#include <SDL.h>
#include <SDL_image.h>

class RenderTest
{
public:
	RenderTest	(void); 
	~RenderTest (void);

	SDL_Renderer*	render;
	SDL_Window*		window;

	int iScreenHeight;
	int iScreenWidth;
};
extern RenderTest* ren;

#endif