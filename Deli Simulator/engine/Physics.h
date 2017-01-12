#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "Box2D/Box2D.h"


class Physics
{
public:
	Physics (void);
	~Physics (void);

	void Step(void);

	void CreatePhysicsBody (b2BodyDef& newobj);

	void SetGravity (int xgrav, int ygrav);
	void SetGravity (float xgrav, float ygrav);

	void GetGravity (void);

	b2World* gWorld;
	int ptom;

private:

	float time_step;

	b2Vec2 gravity;
};
extern Physics* pEngine;

#endif