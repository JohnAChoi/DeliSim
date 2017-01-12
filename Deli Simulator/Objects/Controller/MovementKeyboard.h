#ifndef _MOVEMENT_KEYBOARD_H_
#define _MOVEMENT_KEYBOARD_H_

#include "Controller.h"
#include "../Box2D/Box2D.h"

//This class handles inputs from the keyboard
//Assumes WASD movement for now with left shift to sprint
class MovementKeyboard : public Controller
{
public:
	MovementKeyboard(void);
	~MovementKeyboard(void);

	int GetMove (b2Vec2 *velocity) override;

private:

	uint8_t const *kbState;
};

#endif