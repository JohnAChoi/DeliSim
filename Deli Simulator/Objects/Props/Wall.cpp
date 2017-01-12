#include "Wall.h"

//Pass in the UPPER LEFT corner of the wall along with the height and width IN PIXELS.
Wall::Wall (int x, int y, int width, int height, char* texture)
{
	b2BodyDef wallBodyDef;
	wallBodyDef.position.Set(((x + (float)width/2) / pEngine->ptom), ((y + (float)height/2) / pEngine->ptom));
	wallBodyDef.type = b2_staticBody;
	pBody = pEngine->gWorld->CreateBody(&wallBodyDef);
	
	b2PolygonShape wallBox;
	wallBox.SetAsBox((((float)width/2) / pEngine->ptom), (((float)height/2) / pEngine->ptom));
	pBody->CreateFixture(&wallBox, 0.0f);

	tObjTex = LoadTexture (texture);
	rPosition.h = height;
	rPosition.w = width;
	rPosition.x = pBody->GetPosition().x * pEngine->ptom - rPosition.w / 2;
	rPosition.y = pBody->GetPosition().y * pEngine->ptom - rPosition.h / 2;

	//Arbitrary render depth of 8 for walls
	//May need to change based on where it is in relation to player
	m_render_depth = 8;
}

Wall::Wall (SDL_Rect pos) {}

Wall::~Wall (void) {}

//It's a wall: what do you think it does?
void Wall::OnCreate (void) {}
void Wall::OnDestroy (void) {}
void Wall::Update (void) {}
void Wall::LateUpdate (void) {}

void Wall::Draw (void) 
{
	SDL_RenderCopy ((ren)->render, tObjTex, NULL, &rPosition);
}