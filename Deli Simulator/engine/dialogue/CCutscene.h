#ifndef _C_CUTSCENE_H_
#define _C_CUTSCENE_H_

#include "../Objects/BaseObject.h"
#include <vector>

class CDialogueTree;
class CTextBox;

struct sCutsceneActor
{
	SDL_Texture *pSprite;
	SDL_Rect mPosition;
	SDL_Rect mSprPos;	//Height/width of sprites is saved as h/w
	int sprIndex;		//Current sprite index
	int sprCount;		//Total number of sprites
	int sprRow;			//Number of sprites per row
	std::string mName;
};

//Make it an object so it can handle its own input and other things
class CCutscene: BaseObject
{
public:
	//Default/Test constructor
	CCutscene (void);
	//File constructor
	CCutscene (char *filename);
	
	~CCutscene (void);

	void Update (void) override;
	void LateUpdate (void) override;
	void Draw (void) override;

	bool Ended (void);

private:
	void UpdateScreen (void);

	bool mEnded; 
	bool mPreviouslyPressedSpace;
	bool mPreviouslyPressedBack;
	bool mPrevS;
	bool mPrevW;
	bool mPrevF;
	bool mUpdated;
	const uint8_t *kbState;

	CDialogueTree *pTree;
	CTextBox *pTextBox;
	//Includes all the actors to render to the screen
	std::vector <sCutsceneActor *> mActors;

	int mChoiceIndex;
	std::vector <std::string> mChoices;
	//music
	//backgrounds
};


#endif
