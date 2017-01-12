#ifndef _PLAYER_CHARACTER_H_
#define _PLAYER_CHARACTER_H_

#include "Character.h"

class PlayerCharacter: public Character
{
public:
	//Default Constructor
	PlayerCharacter (void);
	//String Constructor: String should have filepath to texture
	//PlayerCharacter (string *texpath);
	~PlayerCharacter (void);

	void OnCreate	(void) override;
	void OnDestroy	(void) override;

	void Update		(void) override;
	void LateUpdate (void) override;
	//void Draw		(void) override;

	//Set the player's position to a specific location
	void SetPosition (SDL_Rect pos) override;

private:
};
//extern pointer to the Player
//Apparently bad mojo since it's exposed to the OS, not just the program
extern PlayerCharacter* Player;

#endif