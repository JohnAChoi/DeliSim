#include "Character.h"

Character::Character(){}

Character::~Character()
{
	if (pController)
		delete pController;

	pController = NULL;
}

void Character::ChangeController (Controller *con)
{
	//Make sure the new controller is not null, at least
	if (con != NULL)
	{
		//Double check to see if the old one is null, delete it if it isn't
		if (pController)
			delete pController;
		//Set the new controller as the current one
		pController = con;
	}
	//Do nothing if the new controller is null
}