#include "MovementDebug.h"
#include "SDL_keyboard.h"
#include "time/CTime.h"

MovementDebug::MovementDebug(void) 
{
	testbox = NULL;
	mTextCD = 0.0;
	lameCounter = 0;
	testScene = NULL;
}

MovementDebug::~MovementDebug(void)
{
	//Don't have to worry about freeing this memory up since it's handled by SDL
	kbState = NULL;
	if (testbox)
		delete testbox;
	testbox = NULL;
}

//This function takes a pointer to a b2Vec2 to return the velocity
//The int returned is the sprite index (for now)
//Ideally, pass in a b2Vec2 with (0,0)
int MovementDebug::GetMove(b2Vec2 *velocity)
{
	kbState = SDL_GetKeyboardState(NULL);
	int spr_index = 0;

	//Move the player
	//Later on, use an internal mask to allow for custom keyboard configs
	//Also, uses the hardware scan code, so keyboard layout doesn't matter.
	//Abstract to movement class
	if (kbState[SDL_SCANCODE_W])
	{
		spr_index = 1;
		velocity->y -= 1.0;
	}

	if (kbState[SDL_SCANCODE_S])
	{
		spr_index = 0;
		velocity->y += 1.0;
	}

	if (kbState[SDL_SCANCODE_A])
	{
		spr_index = 3;
		velocity->x -= 1.0;
	}

	if (kbState[SDL_SCANCODE_D])
	{
		spr_index = 2;
		velocity->x += 1.0;
	}

	//GOTTA GO FAST -> EVEN FASTER
	if (kbState[SDL_SCANCODE_LSHIFT])
		(*velocity) *= 4;

	//NOW DO FANCY DEBUG STUFF BECAUSE IT'S COOL

	//Test Textbox-ish thing
	if (kbState[SDL_SCANCODE_T] && testbox == NULL)
	{
		std::cout << "Making Textbox" << std::endl;
		testbox = new CTextBox("TEST DATA HERE", "HELLO");
	}

	if (kbState[SDL_SCANCODE_Y] && testbox != NULL && (Time::currentTime - mTextCD) >= .25)
	{
		std::cout << "Advancing text" << std::endl;
		mTextCD = Time::currentTime;
		
		std::string text = "TEST ";
		text.push_back (lameCounter + '0');
		std::string title = "TITLE ";
		title.push_back ('0' + lameCounter);
		lameCounter++;

		testbox->SetText (text);
		testbox->SetTitle (title);
	}

	if (kbState[SDL_SCANCODE_G])
	{
		std::cout << "Testing cutscene" << std::endl;

		if (testScene == NULL)
			testScene = new CCutscene ("./res/CutsceneTest2.txt");
		else
			std::cout << "Cutscene in progress" << std::endl;
	}

	if (kbState[SDL_SCANCODE_H])
	{
		if (testScene && testScene->Ended())
		{
			std::cout << "Deleting Cutscene" << std::endl;
			delete testScene;
			testScene = NULL;
		}
	}

	return spr_index;
}