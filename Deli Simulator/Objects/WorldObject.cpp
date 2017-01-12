#include "WorldObject.h"
#include <iostream>

WorldObject::WorldObject (void):
	BaseObject ()
{
	tObjTex = LoadTexture ("./res/fullres_testimage.png");
}

WorldObject::~WorldObject (void)
{
	//Nothing to delete here yet.
}

void WorldObject::OnCreate	(void)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, ((float)(ren->iScreenHeight)/pEngine->ptom));
	groundBodyDef.type = b2_staticBody;
	b2Body* groundBody = pEngine->gWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox((float)(ren->iScreenWidth/pEngine->ptom), 1.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
}

void WorldObject::OnDestroy	(void)
{
	//PARTY IN THE HOUSE
}

void WorldObject::Update (void)
{
	//Maybe when things get a little more intense
}

void WorldObject::LateUpdate (void)
{
	//Ha
}

void WorldObject::Draw (void)
{
	//Render this object!
	SDL_RenderCopy ((ren)->render, tObjTex, NULL, NULL);
}
