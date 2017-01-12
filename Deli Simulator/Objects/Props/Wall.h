#ifndef _WALL_H_
#define _WALL_H_

#include "Prop.h"

class Wall: public Prop
{
public:
	Wall (int x, int y, int width, int height, char* texture);
	Wall (SDL_Rect pos);
	~Wall (void);

	void OnCreate	(void) override;
	void OnDestroy	(void) override;

	void Update		(void) override;
	void LateUpdate (void) override;
	void Draw		(void) override;
};

#endif