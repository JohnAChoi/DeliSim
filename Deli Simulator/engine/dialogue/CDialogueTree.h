#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include "CDialogueLoader.h"

enum NODE_TYPE
{
	NODE_NULL = 0,
	NODE_LINE,
	NODE_CHOICE,
	NODE_WAIT,
	NODE_END
};

struct DialogueNode
{
	int ID;
	NODE_TYPE type; //Dialogue or Choice, really
	int flags;
	//int length;
	int character;
	int Parent; //Index of the parent node for backtracking
	std::vector<int> Next; //Contains the indexes of the children nodes.
	std::string Line;
	std::vector<sActorAnimation *> actorAnimations;
	//std::string sound;
	std::string Address;
	int Music; //Index of the song for BGM
	int Background; //Index of the image for the background
};

struct ChoiceNode : DialogueNode
{
	std::vector<std::string> Lines;
	std::vector<std::string> choiceJumps;
	int defaultChoice;
};

class CDialogueTree
{
public:
	CDialogueTree (void);
	CDialogueTree (char *file);
	~CDialogueTree (void);

	/*Functions for asset loading*/
	std::vector <sActor *> GetActors (void);
	std::vector <std::string> GetBackgroundList (void);
	std::vector <std::string> GetMusicList (void);

	/*Functions related to advancing the dialogue*/

	//Go to the next line of dialogue
	void AdvanceDialogue (void);
	//Report the player's choice
	int ReportChoice (int choice = -1); 
	//Go back one line of dialogue
	int Backtrack (void);

	/*Functions for getting data about the current line of dialogue*/

	//Get the line as a C-string
	const char *GetLine (void);
	//Get the choices
	std::vector<std::string> GetChoices (void);
	//Get the flags
	int GetFlags (void);
	//Get the length
	int GetLength (void);
	//Get the index for the character speaking the line, aka TITLE
	int GetCharacter (void);
	//Get all of the animation info for the line
	std::vector <sActorAnimation *> GetAnimations (void);

	/*GetCharacter (void);
	GetMotionData (void);
	GetSoundData (void);*/

	//Prints the contents of the tree to cout
	void PrintTree (void);

	NODE_TYPE sNodeType;

private:
	void CreateTree (char * file);
	void DestroyTree (void);
	void CreateLinks (void);

	CDialogueLoader *pLoader;

	/*DialogueNode *mRoot; 
	DialogueNode *mCurrent;*/

	std::vector <std::string> backgroundList;
	std::vector <std::string> musicList;
	std::vector <sActor *> actorList;

	//Root is obviously position 0
	std::vector<DialogueNode *> mTree; //Store all the nodes in a vector for easy management
	int mCurrent; //index of current line of dialogue
};