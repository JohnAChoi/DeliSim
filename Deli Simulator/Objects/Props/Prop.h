#ifndef _PROP_H_
#define _PROP_H_

#include "../Actor.h"

class Prop: public Actor
{
public:
	Prop (void);
	Prop (SDL_Rect pos);
	~Prop (void);

	void OnCreate	(void) override;
	void OnDestroy	(void) override;

	void Update		(void) override;
	void LateUpdate (void) override;
	void Draw		(void) override;
};

#endif