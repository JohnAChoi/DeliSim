#ifndef _MOVEMENT_DEBUG_H_
#define _MOVEMENT_DEBUG_H_

#include "Controller.h"
#include "../Box2D/Box2D.h"
#include "../UI/CTextbox.h"
#include "../engine/dialogue/CCutscene.h"
#include "../engine/types/floattype.h"

//This class handles inputs from the keyboard
//Also includes some nifty commands for debugging crap
class MovementDebug : public Controller
{
public:
	MovementDebug(void);
	~MovementDebug(void);

	int GetMove(b2Vec2 *velocity) override;

private:

	uint8_t const *kbState;
	CTextBox *testbox;
	CCutscene *testScene;
	ftype mTextCD;
	int lameCounter;
};

#endif