#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include <SDL.h>

#include "../BaseObject.h"
#include <string>
#include <vector>
#include <SDL_ttf.h>

//Inherit from BaseObject since the Textbox just needs to render to the screen and wait for some input
class Textbox : public BaseObject
{
public:
	//Constructors
	Textbox (void);
	//Textbox (file pointer or some shit);
	//Textbox (string I guess);
	~Textbox (void);

	void Update(void) override;
	//void LateUpdate(void) override;
	void Draw(void) override;

	//Show the next message: true means the textbox still has a message to show, false means it's done
	bool AdvanceText(void);

	//Need a load convo function?
private:

	bool AdvanceTextInstant(void);

	//void putchar()? yes. Sometime
	//Index for the convo
	int mIndex;
	//Each string should constitute all the text shown on one box
	std::vector<std::string> mMessages;
	//Parallel vector to mMessages: should display a title for each message as well
	std::vector<std::string> mTitles;
	//Font to right in
	TTF_Font *pFont;
	//Set color of text
	SDL_Color textColor;
	//Texture for the text to render
	SDL_Texture *pText;
	SDL_Rect rPositionText;
	//Texture for the title to render
	SDL_Texture *pTitle;
	SDL_Rect rPositionTitle;
	//Use the base tObjTex and rPosition from BaseObject for the background box
};

#endif

/*Text files that contain the text should be formatted like HTML headers:
Name: This is the message that the character is speaking
Will use special characters to denote jumps for decisions
Special way of handling font?*/