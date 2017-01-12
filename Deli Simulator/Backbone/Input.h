#ifndef _INPUT_H_
#define _INPUT_H_

#include <SDL.h>

class Input
{
public:
	Input (void);
	~Input (void);

	void GetRawInput (void);

	SDL_Event eInput;
};
extern Input Inputs;
/*This last line makes this a global instance. Technically a no-no for C++, but this is my shit.
Should use a static class, but it's a pain in the butt.
Have to declare each function and data member as static and then redeclare them in the .cpp.
Avoid this by having a Global class that contains this? Probably. That sounds a lot better.
*/
#endif