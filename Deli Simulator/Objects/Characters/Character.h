#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "../Actor.h"
#include "../Controller/Controller.h"

//Yes, this class is solely to add a Controller so that Props wouldn't have them
//SUE ME, FUCKER
class Character : public Actor
{
public:
	Character();
	~Character();

	//Use this to change controllers
	//Likely useful for cutscenes, maybe battles?
	void ChangeController (Controller *con);

protected:
	Controller *pController;
};

#endif
