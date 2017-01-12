#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include <SDL.h>
#include "engine\Behavior.h"
#include "../Renderer/RenderTest.h"
#include "Physics.h"

class BaseObject: public Engine::Behavior
{
public:
	BaseObject (void);
	BaseObject (SDL_Rect start_pos, char* texture_name);
	BaseObject (char* texture_name);
	~BaseObject (void);

	void OnCreate	(void) override;
	void OnDestroy	(void) override;

	void Update		(void) override;
	void LateUpdate (void) override;
	void Draw		(void) override;

	SDL_Rect* GetPosition (void);
	virtual void SetPosition (SDL_Rect new_pos);

protected:
	SDL_Texture* LoadTexture (char* texname);
	//Location on screen (Pixel coordinates
	SDL_Rect rPosition;
	//Texture for the object
	SDL_Texture* tObjTex;
};

#endif