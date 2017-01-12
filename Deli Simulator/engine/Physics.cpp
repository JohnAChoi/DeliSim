#include "Physics.h"
#include "Engine/time/CTime.h"
#include <iostream>

Physics* pEngine = NULL;

Physics::Physics(void)
{
	pEngine = this;
	gravity.x = (0.0f);
	gravity.y = (0.0f);
	time_step = 1.0f / 60.0f;

	gWorld = new b2World(gravity);
	//gWorld->SetGravity(gravity);

	//1 meter here = 64 pixels on screen for now.
	ptom = 64;
}

Physics::~Physics(void)
{
	if (gWorld)
	{
		delete gWorld;
	}
	gWorld = NULL;
}

void Physics::Step (void)
{
	float elapsed_time = 0.0;
	while (elapsed_time < CTime::deltaTime)
	{
		//See if this sorcery works
		gWorld->Step(time_step, 8, 3);
		elapsed_time += time_step;
		//gWorld->Dump();
	}
}

//Positive x gravity goes to the right of the screen
//Positive y gravity goes to the top of the screen
void Physics::SetGravity(int xgrav, int ygrav)
{
	gravity.x = xgrav;
	gravity.y = ygrav;
	gWorld->SetGravity(gravity);
}

void Physics::SetGravity(float xgrav, float ygrav)
{
	gravity.x = xgrav;
	gravity.y = ygrav;
	gWorld->SetGravity(gravity);
}