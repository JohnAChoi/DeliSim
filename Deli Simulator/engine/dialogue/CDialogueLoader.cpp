#include "CDialogueLoader.h"
#include <fstream>
#include <algorithm>
#include <functional>
#include <cctype>

CDialogueLoader::CDialogueLoader (void)
{
	depth = 0;
	lineNumber = 0;
	sState = DIALOGUE_START;
	pHandle = new std::ifstream("test.txt");
	PreLoad();
}

CDialogueLoader::CDialogueLoader (char * filename)
{
	depth = 0;
	lineNumber = 0;
	sState = DIALOGUE_START;
	pHandle = new std::ifstream (filename); //Opens for read by default since it's an input stream. duh.
	PreLoad();
}

CDialogueLoader::~CDialogueLoader (void)
{
	if (pHandle)
	{
		pHandle->close();
		delete pHandle;
	}
	pHandle = NULL;

	//DELETE EVERYTHING ELSE!
}

//General note: The EOF checks are everywhere because I'd rather clutter this up and prevent an infinite loop/nasty crash
void CDialogueLoader::PreLoad (void)
{
	//Go to the start tag
	while (currentLine.find ("#Begin") == std::string::npos && !pHandle->eof())
		loaderGetLine();

	//Load all assets!
	while (currentLine.find ("#Scene") == std::string::npos && !pHandle->eof())
	{
		if (depth == 0)
		{
			if (currentLine.find ("Actor") != std::string::npos)
				MakeActor();
			else if (currentLine.find ("Background") != std::string::npos)
				MakeBackgrounds();
			else if (currentLine.find ("Music") != std::string::npos)
				MakeMusic();
			//else something weird is in here
		}

		loaderGetLine();
	}
}

void CDialogueLoader::MakeActor (void)
{
	sActor *currentActor = new sActor();

	loaderGetLine(); //Line should be "{"

	//if (currentLine.find ("{") != std::string::npos)
		//depth++;
	//else how did I get here?

	while (depth == 1)
	{
		if (header.compare ("name") == 0)
			currentActor->name = value; //Get the name
		else if (header.compare ("file") == 0)
			currentActor->file = value; //Get the file name
		else if (header.compare ("width") == 0)
			currentActor->width = std::atoi (value.c_str());
		else if (header.compare ("height") == 0)
			currentActor->height = std::atoi (value.c_str());
		else if (header.compare ("row") == 0)
			currentActor->row = std::atoi (value.c_str());
		else if (header.compare ("count") == 0)
			currentActor->count = std::atoi (value.c_str());
		//Should probably have an error message in here
		loaderGetLine();
	}
	actorList.push_back(currentActor);
}

void CDialogueLoader::MakeBackgrounds (void)
{
	loaderGetLine(); //Line should be "{"

	while (depth == 1)
	{
		if (header.compare ("file") == 0)
			backgroundList.push_back (value);
		//Shouldn't be anything else inside. For now
		
		loaderGetLine();
	}
}

void CDialogueLoader::MakeMusic (void)
{
	loaderGetLine(); //Line should be "{"

	while (depth == 1)
	{
		if (header.compare ("file") == 0)
			musicList.push_back (value);

		//Shouldn't be anything else inside. For now

		loaderGetLine();
	}
}

//Go to the next object and load it up
void CDialogueLoader::NextObject (void)
{
	animationList.clear();
	choiceList.clear();

	while (depth == 0) // && !pHandle->eof())
	{
		if (currentLine.find ("Line") != std::string::npos)
			sState = DIALOGUE_LINE;
		else if (currentLine.find ("Choice") != std::string::npos)
			sState = DIALOGUE_CHOICE;
		else if (currentLine.find ("#End") != std::string::npos || pHandle->eof())
		{
			sState = DIALOGUE_END;
			return;
		}

		//ERROR MESSAGE OR SOMETHING IS PROBABLY A GOOD IDEA

		loaderGetLine();
	}

	while (depth == 1 && !pHandle->eof()) //Handle the actual line
	{
		if (header.compare ("address") == 0)
			Address = value;
		else if (header.compare ("speaker") == 0)
			Actor = std::atoi (value.c_str());
		else if (header.compare ("line") == 0)
			Line = value;
		else if (header.compare ("audio") == 0)
			Audio = value;
		else if (header.compare ("track") == 0)
		{
			if (value.empty())
				Track = -1;
			else
				Track = std::atoi (value.c_str());
		}
		else if (header.compare ("background") == 0)
		{
			if (value.empty())
				Background = -1;
			else
				Background = std::atoi (value.c_str());
		}
		else if (currentLine.find("Actor") != std::string::npos)
			LoadAnimation();
		else if (currentLine.find ("Option")  != std::string::npos)
			LoadOption();

		loaderGetLine();
	}
}

void CDialogueLoader::LoadAnimation (void)
{
	sActorAnimation *pAnimation = new sActorAnimation();

	pAnimation->index = std::atoi (currentLine.substr (6).c_str());

	loaderGetLine(); //Line should be "{"

	while (depth == 2 && !pHandle->eof()) //Handle Actors and Choices
	{
		if (header.compare ("x") == 0)
			pAnimation->x = std::atoi(value.c_str());
		else if (header.compare ("y") == 0)
			pAnimation->y = std::atoi(value.c_str());
		else if (header.compare ("spriteindex") == 0)
			pAnimation->sprIndex = std::atoi(value.c_str());
		/*else if (currentLine.find("animation") != std::string::npos)
		{
			//TODO: ANIMATION SUPPORT
		}*/

		loaderGetLine();
	}

	animationList.push_back(pAnimation);
}

void CDialogueLoader::LoadOption (void)
{
	sChoice *pChoice = new sChoice();

	loaderGetLine(); //Line should be "{"

	while (depth == 2 && !pHandle->eof()) //Handle Actors and Choices
	{
		if (header.compare ("destination") == 0)
			pChoice->dest = value;
		else if (header.compare ("line") == 0)
			pChoice->line = value;

		loaderGetLine();
	}
	choiceList.push_back(pChoice);
}

DialogueState CDialogueLoader::GetState (void)
{
	return sState;
}

const char * CDialogueLoader::GetLine (void)
{
	return Line.c_str();
}

const char * CDialogueLoader::GetAddress (void)
{
	return Address.c_str();
}

int CDialogueLoader::GetCurrentSpeaker (void)
{
	return Actor;
}

const char * CDialogueLoader::GetAudio (void)
{
	return Audio.c_str();
}

int CDialogueLoader::GetMusic (void)
{
	return Track;
}

int CDialogueLoader::GetBackground (void)
{
	return Background;
}

std::vector<sActor *> CDialogueLoader::GetActors (void)
{
	return actorList;
}

std::vector<sChoice *> CDialogueLoader::GetChoices (void)
{
	return choiceList;
}

std::vector<sActorAnimation *> CDialogueLoader::GetAnimations (void)
{
	return animationList;
}

std::vector<std::string> CDialogueLoader::GetMusicList (void)
{
	return musicList;
}

std::vector<std::string> CDialogueLoader::GetBackgroundList (void)
{
	return backgroundList;
}

//This function is here solely to remove comments from the dialogue file
void CDialogueLoader::loaderGetLine (void)
{
	currentLine.clear();
	header.clear();
	value.clear();

	std::getline(*pHandle, currentLine);
	lineNumber++;

	//Remove comments from the line
	int index = currentLine.find_first_of ('/');
	if (index > -1 && currentLine[index + 1] == '/')
		currentLine = currentLine.substr (0, index);

	//Trim the left side
	currentLine.erase (currentLine.begin(), std::find_if(currentLine.begin(), currentLine.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	//Trim the right side
	currentLine.erase (std::find_if(currentLine.rbegin(), currentLine.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), currentLine.end());
	//http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

	size_t colon = currentLine.find_first_of (":");

	if (colon != std::string::npos)
	{
		//Get header and trim again, just in case
		header = currentLine.substr (0, colon);
		header.erase(std::find_if(header.rbegin(), header.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), header.end()); 

		//Make sure there's a possible value and then trim it
		if (colon + 1 < currentLine.size())
		{
			value = currentLine.substr (colon + 1);
			value.erase(value.begin(), std::find_if(value.begin(), value.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		}
	}

	if (currentLine.find ("}") != std::string::npos)
		depth--;
	else if (currentLine.find ("{") != std::string::npos)
		depth++;
	//return currentLine;
}