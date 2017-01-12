#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "../Box2D/Box2D.h"

//Base class for the Controller
//Each character should have one to control its movement
class Controller
{
public:
	Controller();
	~Controller();

	//Get the velocity for the current frame
	//Returns the sprite index (probably) and the b2Vec2 pointer is how the velocity is returned
	virtual int GetMove(b2Vec2 *velocity);

	//May need additional functionality to handle other inputs,
	//such as interacting with objects and attacking
	//Menu will be handled by this class as well. Somehow

private:
};

#endif