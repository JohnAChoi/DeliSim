#include "CCutscene.h"
#include "SDL_keyboard.h"
#include "CDialogueTree.h"
#include "Objects/UI/CTextbox.h"

CCutscene::CCutscene (void)
{
	//?
}

CCutscene::CCutscene (char *filename)
{
	pTree = new CDialogueTree (filename);
	pTextBox = new CTextBox ();

	std::vector <sActor *> actors = pTree->GetActors();

	sCutsceneActor *temp = NULL;

	for (auto iter = actors.begin(); iter != actors.end(); iter++)
	{
		temp = new sCutsceneActor ();
		//The 4 lines of code are here to demonstrate that, at heart, I'm a C programmer. I just have OO needs.
		char * spriteName = (char *)malloc((*iter)->file.size() + 1);
		for (int i = 0; i < (*iter)->file.size(); i++)
			spriteName[i] = (*iter)->file[i];
		spriteName[(*iter)->file.size()] = 0;

		temp->mName = (*iter)->name;
		//Load the sprite
		temp->pSprite = LoadTexture (spriteName);
		//Do not render by default
		temp->sprIndex = -1;
		temp->sprCount = (*iter)->count;
		temp->sprRow = (*iter)->row;

		//Specify height and width in the file, someday: That someday is NOW
		temp->mPosition.h = (*iter)->height;
		temp->mPosition.w = (*iter)->width;
		temp->mPosition.x = 0;
		temp->mPosition.y = 0;

		temp->mSprPos.h = (*iter)->height;
		temp->mSprPos.w = (*iter)->width;
		temp->mSprPos.x = 0;
		temp->mSprPos.y = 0;

		//Free the memory used to prevent a memory leak
		free (spriteName);

		mActors.push_back (temp);
	}

	mPreviouslyPressedBack = false;
	mPreviouslyPressedSpace = false;
	mPrevS = false;
	mPrevW = false;
	mPrevF = false;
	mUpdated = false;
	mChoiceIndex = 0;

	//Get backgrounds and music later
	UpdateScreen();
}

CCutscene::~CCutscene (void)
{
	kbState = NULL;
	
	if (pTree)
		delete pTree;
	pTree = NULL;

	if (pTextBox)
		delete pTextBox;
	pTextBox = NULL;

	for (auto iter = mActors.begin(); iter != mActors.end(); iter++)
	{
		if ((*iter)->pSprite)
			SDL_DestroyTexture ((*iter)->pSprite);
		(*iter)->pSprite = NULL;
		delete (*iter);
	}

	mActors.clear();
}

void CCutscene::UpdateScreen (void)
{
	if (pTree->sNodeType == NODE_END)
	{
		//Go set that global variable
		mEnded = true;
		return;
	}
	if (!mUpdated) //Only needs to be updated when the text would change
	{
		//This stuff always needs to be updated
		int title = pTree->GetCharacter();
		const char * line = pTree->GetLine();
		std::vector <sActorAnimation *> animations = pTree->GetAnimations();

		for (auto iter = animations.begin(); iter != animations.end(); iter++)
		{
			mActors[(*iter)->index]->sprIndex = (*iter)->sprIndex;
			
			if (mActors[(*iter)->index]->sprIndex > mActors[(*iter)->index]->sprCount)
				mActors[(*iter)->index]->sprIndex = mActors[(*iter)->index]->sprCount; //Should probably throw an error here

			mActors[(*iter)->index]->mSprPos.x = (mActors[(*iter)->index]->sprIndex % mActors[(*iter)->index]->sprRow) * mActors[(*iter)->index]->mSprPos.w;
			mActors[(*iter)->index]->mSprPos.y = (mActors[(*iter)->index]->sprIndex / mActors[(*iter)->index]->sprRow) * mActors[(*iter)->index]->mSprPos.h;

			mActors[(*iter)->index]->mPosition.x = (*iter)->x;
			mActors[(*iter)->index]->mPosition.y = (*iter)->y;
		}

		pTextBox->SetText (line);
		pTextBox->SetTitle (mActors[title]->mName.c_str());
	
		//Only necessary if we've moved to a choice
		if (pTree->sNodeType == NODE_CHOICE)
		{
			mChoices = pTree->GetChoices();
			pTextBox->SetChoices (mChoices);
		}
		mUpdated = true;
	}
}

void CCutscene::Update (void)
{
	//Something something check a flag to make sure this is active? I guess?
	kbState = SDL_GetKeyboardState (NULL);

	//Advance and backtrack the cutscene
	if (kbState[SDL_SCANCODE_SPACE] && !mPreviouslyPressedSpace) //Catches keydown event only
	{
		mPreviouslyPressedSpace = true;
		
		if (pTree->sNodeType == NODE_LINE)
		{
			pTree->AdvanceDialogue();
			mUpdated = false;
		}
	}
	else if (kbState[SDL_SCANCODE_BACKSPACE] && !mPreviouslyPressedBack)
	{
		mPreviouslyPressedBack = true;
		pTree->Backtrack(); //Always able to go back
		mUpdated = false;
	}

	if (!kbState[SDL_SCANCODE_SPACE])
		mPreviouslyPressedSpace = false;

	if (!kbState[SDL_SCANCODE_BACKSPACE])
		mPreviouslyPressedBack = false;

	//Get cursor controls
	if (kbState[SDL_SCANCODE_S] && !mPrevS)
	{
		if (mChoices.size() > 0) //Only check if there are actually choices on screen
		{
			mChoiceIndex++;
			mChoiceIndex %= mChoices.size();
			pTextBox->SetCursorIndex(mChoiceIndex);
		}
		mPrevS = true;
	}
	else if (kbState[SDL_SCANCODE_W] && !mPrevW)
	{
		if (mChoices.size() > 0)
		{
			mChoiceIndex--;
		
			if (mChoiceIndex < 0)
				mChoiceIndex = mChoices.size() - 1;

			pTextBox->SetCursorIndex (mChoiceIndex);
		}
		mPrevW = true;
	}
	else if (kbState[SDL_SCANCODE_F] && !mPrevF)
	{
		if (pTree->sNodeType == NODE_CHOICE)
		{
			pTree->ReportChoice (mChoiceIndex);
			pTextBox->ClearChoices();
			mUpdated = false;
		}
		mPrevF = true;
	}


	if (!kbState[SDL_SCANCODE_S])
		mPrevS = false;

	if (!kbState[SDL_SCANCODE_W])
		mPrevW = false;

	if (!kbState[SDL_SCANCODE_F])
		mPrevF = false;
}

//This is the first usage of LateUpdate in the DeliSim Engine!
void CCutscene::LateUpdate (void)
{
	UpdateScreen();
}

void CCutscene::Draw (void)
{
	for (auto iter = mActors.begin(); iter != mActors.end(); iter++)
	{
		if ((*iter)->sprIndex > -1)
			SDL_RenderCopy((ren)->render, (*iter)->pSprite, &((*iter)->mSprPos), &((*iter)->mPosition));
	}
}

//Returns true if the cutscene is over
bool CCutscene::Ended (void)
{
	return mEnded;
}