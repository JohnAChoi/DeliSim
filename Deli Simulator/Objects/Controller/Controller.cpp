#include "Controller.h"

Controller::Controller() {}
Controller::~Controller(){}

//Just some default behavior
//It won't move, which may make something later on really annoying
int Controller::GetMove(b2Vec2 *velocity)
{
	velocity->x = 0;
	velocity->y = 0;
	return 0;
}