#ifndef _C_DIALOGUE_LOADER_H_
#define _C_DIALOGUE_LOADER_H_

#include <string>
#include <vector>
#include <iostream>

enum DialogueState
{
	DIALOGUE_NULL = 0,
	DIALOGUE_START,
	DIALOGUE_ACTORS,
	DIALOGUE_LINE,
	DIALOGUE_CHOICE,
	DIALOGUE_END,
};

struct sActor
{
	std::string name;
	std::string file;
	int width;
	int height;
	int row;
	int count;
};

struct sActorAnimation
{
	int index;
	int x;
	int y;
	int sprIndex;
	//Animation? Not sure
};

struct sChoice
{
	std::string dest;
	std::string line;
};

class CDialogueLoader
{
public:
	CDialogueLoader (void);
	CDialogueLoader (char * filename);
	~CDialogueLoader (void);

	DialogueState GetState (void);

	//Getters for info
	std::vector <std::string> GetMusicList (void);
	std::vector <std::string> GetBackgroundList (void);
	std::vector <sActor *> GetActors (void);

	const char * GetLine (void);	
	const char * GetAddress (void);
	int GetCurrentSpeaker (void);
	const char * GetAudio (void);
	int GetMusic (void);
	int GetBackground (void);

	std::vector <sChoice *> GetChoices (void);
	std::vector <sActorAnimation *> GetAnimations (void);

	//Read the next object in
	void NextObject (void);

//Loader state info
private:
	//Gets a line while removing comments
	void loaderGetLine (void);

	/*Internal State info*/
	std::ifstream *pHandle;
	int depth;
	DialogueState sState;	//Don't make this public because I have a modicum of software design sense
	std::string currentLine;
	std::string header;
	std::string value;
	int lineNumber;

/*Asset loading stuff*/
private:
	void PreLoad (void);
	void MakeActor (void);
	void MakeBackgrounds (void);
	void MakeMusic (void);

	std::vector<std::string> backgroundList;
	std::vector<std::string> musicList;
	std::vector <sActor *> actorList;

/*Line information*/
private:

	void LoadAnimation (void);
	void LoadOption (void);

	//Animation List
	std::vector <sActorAnimation *> animationList;
	//Choice list
	std::vector <sChoice *> choiceList;
	//Current Data
	std::string Line;
	std::string Address;
	int Actor;
	int Track;
	int Background;
	std::string Audio; //Can probably leave this out for a while. Probably.
};

#endif
