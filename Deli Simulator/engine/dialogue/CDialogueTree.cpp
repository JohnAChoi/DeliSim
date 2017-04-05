#include "CDialogueTree.h"
#include <iostream>
#include <queue>

//Create the tree
CDialogueTree::CDialogueTree (void)
{
	//Generic tree for testing functions, I think
	sNodeType = NODE_NULL;
	mCurrent = 0;
	CreateTree ("test2.txt");
	CreateLinks();

	sNodeType = mTree[mCurrent]->type;

	actorList = pLoader->GetActors();
	backgroundList = pLoader->GetBackgroundList();
	musicList = pLoader->GetMusicList();

	if (pLoader)
		delete pLoader;
	pLoader = NULL;
}

//Load from a given file
CDialogueTree::CDialogueTree (char * file)
{
	//Herro there
	mCurrent = 0;
	CreateTree (file);
	CreateLinks();

	sNodeType = mTree[mCurrent]->type;

	actorList = pLoader->GetActors();
	backgroundList = pLoader->GetBackgroundList();
	musicList = pLoader->GetMusicList();

	if (pLoader)
		delete pLoader;
	pLoader = NULL;
}

CDialogueTree::~CDialogueTree (void)
{
	//Destroy everything because it's now worthless
	DestroyTree();

	/*mRoot = nullptr;
	mCurrent = nullptr;*/
}

void CDialogueTree::CreateTree (char * file)
{
	//LOAD THE DAMN THING
	pLoader = new CDialogueLoader (file);

	std::queue<sChoice> mBranches;
	std::string currentAddress = ""; //Just make sure it's properly initialized
	DialogueNode *current;
	ChoiceNode *currentChoice;
	std::vector<sChoice*> Choices;

	while (pLoader->GetState() != DialogueState::DIALOGUE_END)
	{
		switch (pLoader->GetState())
		{
		case DIALOGUE_START:
			break;
		case DIALOGUE_LINE:
			current = new DialogueNode();

			current->ID = mTree.size();			
			current->type = NODE_LINE; //Regular dialogue line
			//What flags did I need again?
			//ignore length here
			
			current->character = pLoader->GetCurrentSpeaker();
			current->Address = pLoader->GetAddress();
			current->Line = pLoader->GetLine();
			current->actorAnimations = pLoader->GetAnimations();
			//current->sound = pLoader->GetCurrentAudio();
			current->Next.push_back(mTree.size() + 1); //Mark the next struct as the child
			current->Parent = mTree.size() - 1; //Handy trick: this makes the Parent of the first node -1 by default
			current->Music = pLoader->GetMusic();
			current->Background = pLoader->GetBackground();

			mTree.push_back(current);
			break;
		case DIALOGUE_CHOICE:
			currentChoice = new ChoiceNode();

			currentChoice->ID = mTree.size();
			currentChoice->type = NODE_CHOICE; //Decision
			//What flags did I need again?
			//ignore length here

			currentChoice->character = pLoader->GetCurrentSpeaker();
			currentChoice->Line = pLoader->GetLine();
			currentChoice->Address = pLoader->GetAddress();
			currentChoice->defaultChoice = 0; //This could be subject to change later on
			Choices = pLoader->GetChoices();

			for (int i = 0; i < Choices.size(); i++)
			{
				currentChoice->Lines.push_back (Choices[i]->line);
				currentChoice->choiceJumps.push_back (Choices[i]->dest);
			}

			currentChoice->actorAnimations = pLoader->GetAnimations();
			//currentChoice->sound = pLoader->GetCurrentAudio();
			currentChoice->Next; //Do I need this if I just store the choices and addresses anyway?
			currentChoice->Parent = mTree.size() - 1;
			currentChoice->Music = pLoader->GetMusic();
			currentChoice->Background = pLoader->GetBackground();

			mTree.push_back(currentChoice);
			break;
		default:
			//Debug::Console->PrintWarning("Unhandled dialogue option\n");
			std::cout << "How did we get here?" << std::endl;
			break;
		}

		pLoader->NextObject();
	}
}

//This creates the links between the choices and the branches
void CDialogueTree::CreateLinks (void)
{
	int index = 0;

	for (; index < mTree.size(); index++)
	{
		if (mTree[index]->type == NODE_CHOICE) //If this is a choice
		{
			ChoiceNode *current = (ChoiceNode *)(mTree[index]);

			//Make a link for each choice
			for (int i = 0; i < current->choiceJumps.size(); i++)
			{
				//Search the rest of the dialogue tree for the branch
				for (int j = 0; j < mTree.size(); j++)
				{
					if (current->choiceJumps[i].empty()) //Go to next node if the address for this one is empty
					{
						current->Next.push_back(index + 1);
						break;
					}
					else if (strcmp (mTree[j]->Address.c_str(), current->choiceJumps[i].c_str()) == 0)
					{
						current->Next.push_back(j); //Set the branch destination
						if (j > index)
							mTree[j]->Parent = index; //Set the parent of the branch

						break;
					}
				}
			}
		}
	}
}

void CDialogueTree::DestroyTree (void)
{
	for (int i = 0; i < mTree.size(); i++)
	{
		while (mTree[i]->actorAnimations.size() > 0)
		{
			delete mTree[i]->actorAnimations.back();
			mTree[i]->actorAnimations.pop_back();
		}

		if (mTree[i]->type == NODE_CHOICE)
		{
			ChoiceNode *current = (ChoiceNode *)(mTree[i]);
			current->choiceJumps.clear();
			current->Lines.clear();
		}

		mTree[i]->Line.clear();

		if (mTree[i])
			free(mTree[i]);
		mTree[i] = nullptr;
	}

	mTree.clear();
}

void CDialogueTree::AdvanceDialogue (void)
{
	if (mTree[mCurrent]->type == NODE_LINE)
	{
		if (mTree[mCurrent]->Next[0] >= mTree.size() || mTree[mTree[mCurrent]->Next[0]]->Parent != mCurrent)
		{
			sNodeType = NODE_END;
			return;
		}

		mCurrent = mTree[mCurrent]->Next[0]; //Go to the next node
		sNodeType = mTree[mCurrent]->type;
	}
	else if (mTree[mCurrent]->type == NODE_CHOICE)
		std::cout << "Error: Current node is a choice. Call ReportChoice() instead" << std::endl;
	else
		std::cout << "lolwut?" << std::endl;
}

//This should probably return the next line of dialogue instead
int CDialogueTree::ReportChoice (int choice)
{
	if ((choice < mTree[mCurrent]->Next.size() && choice >= 0) || choice == -1) 
	{
		if (choice == -1) //-1 is default choice
			choice = ((ChoiceNode *)mTree[mCurrent])->defaultChoice;
		mCurrent = mTree[mCurrent]->Next[choice];
	}
	else
		std::cout << "Error: Invalid choice reported " << choice << std::endl; //Maybe make an exception here later?

	if (mTree[mCurrent]->Next[0] >= mTree.size() || mTree[mTree[mCurrent]->Next[0]]->Parent != mCurrent)
	{
		sNodeType = NODE_END;
		return mCurrent;
	}

	sNodeType = mTree[mCurrent]->type;

	return mCurrent;
}

//Returns the index of the new current node
int CDialogueTree::Backtrack (void)
{
	if (mTree[mCurrent]->Parent > -1)
		mCurrent = mTree[mCurrent]->Parent;

	sNodeType = mTree[mCurrent]->type;

	return mCurrent;
}

const char * CDialogueTree::GetLine (void)
{
	return mTree[mCurrent]->Line.c_str();
}

std::vector<std::string> CDialogueTree::GetChoices (void)
{
	if (mTree[mCurrent]->type == NODE_CHOICE)
		return ((ChoiceNode *)mTree[mCurrent])->Lines;
	std::cout << "Error: Calling GetChoices() when node is a Line type. Call GetLine() instead" << std::endl;
	std::vector<std::string> empty;
	return empty; //There's gotta be a better way
}

int CDialogueTree::GetFlags (void)
{
	return mTree[mCurrent]->flags;
}

int CDialogueTree::GetLength (void)
{
	return 0;
}

//Strictly for debugging
void CDialogueTree::PrintTree (void)
{
	for (int i = 0; i < mTree.size(); i++)
	{
		if (mTree[i]->type == NODE_LINE)
		{
			DialogueNode *current = mTree[i];

			std::cout << "ID: " << current->ID << " " << "Character: " << current->character << '\n';
			std::cout << "Address: " << current->Address << " Flags: " << current->flags << '\n';
			std::cout << "Line: " << current->Line << '\n';
			std::cout << "Parent: " << current->Parent << " | " << "Next: " << current->Next[0] << '\n';

			for (int i = 0; i < current->actorAnimations.size(); i++)
			{
				std::cout << "Actor " << current->actorAnimations[i]->index << ":\n";
				std::cout << "( " << current->actorAnimations[i]->x << ", " << current->actorAnimations[i]->y << ") ";
				std::cout << current->actorAnimations[i]->sprIndex << '\n';
			}
			//std::cout << "Sound: " << current->sound << '\n';
			//std::cout << "Motion: " << current->motion << '\n';
		}
		else if (mTree[i]->type == NODE_CHOICE)
		{
			ChoiceNode *current = (ChoiceNode *)mTree[i];
			std::cout << "ID: " << current->ID << " " << "Character: " << current->character << '\n';
			std::cout << "Address: " << current->Address << " Flags: " << current->flags << '\n';
			std::cout << "Lines:\n";
			for (int j = 0; j < current->Lines.size(); j++)
				std::cout << current->Lines[j] << '\n';
			std::cout << "Parent: " << current->Parent << "\nNext:\n";
			for (int k = 0; k < current->Next.size(); k++)
				std::cout << current->Next[k] << '\n';
			for (int i = 0; i < current->actorAnimations.size(); i++)
			{
				std::cout << "Actor " << current->actorAnimations[i]->index << ":\n";
				std::cout << "( " << current->actorAnimations[i]->x << ", " << current->actorAnimations[i]->y << ") ";
				std::cout << current->actorAnimations[i]->sprIndex << '\n';
			}
			//std::cout << "Sound: " << current->sound << '\n';
			//std::cout << "Motion: " << current->motion << '\n';
		}
	}
}

std::vector <sActor *> CDialogueTree::GetActors(void)
{
	return actorList;
}

std::vector <std::string> CDialogueTree::GetBackgroundList(void)
{
	return backgroundList;
}

std::vector <std::string> CDialogueTree::GetMusicList(void)
{
	return musicList;
}

int CDialogueTree::GetCharacter (void)
{
	return mTree[mCurrent]->character;
}

std::vector <sActorAnimation *> CDialogueTree::GetAnimations (void)
{
	return mTree[mCurrent]->actorAnimations;
}

/*
CDialogueTree::GetSound (void)
CDialogueTree::GetMotion (void)
CDialogueTree::GetCharacter (void)
*/
