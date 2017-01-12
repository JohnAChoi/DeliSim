#include "Actor.h"

Actor::Actor (void):
	BaseObject ()
{
	mSpriteIndex = 0;
	pBody = NULL;
}

Actor::~Actor (void)
{
	if (pBody)
	{
		//Remove it from the physics world
		//Box2D handles the stuff on the other side, so no need for delete here
		pEngine->gWorld->DestroyBody(pBody);
		pBody = NULL;
	}
}

void Actor::OnCreate (void) {}

void Actor::OnDestroy (void) {}

void Actor::Update (void) {}

void Actor::LateUpdate (void) {}

void Actor::Draw (void)
{
	SDL_RenderCopy ((ren)->render, tObjTex, NULL, &rPosition);
}

void Actor::OnInteract (void) {}

b2Body* Actor::GetBody (void)
{
	return pBody;
}