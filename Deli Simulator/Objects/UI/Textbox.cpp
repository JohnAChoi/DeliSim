#include "Textbox.h"

Textbox::Textbox (void)
{
	mIndex = 0;
	m_render_depth = 1;

	//Apparently I don't have to create these vectors with new
	mMessages.push_back ("Default message");
	mMessages.push_back ("Second Message");
	mMessages.push_back ("Third Message");

	mTitles.push_back ("Speaker 1");
	mTitles.push_back ("Speaker 2");
	mTitles.push_back ("Who?");

	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;
	textColor.a = 255;

	pFont = TTF_OpenFont("./res/PixelOperator.ttf", 32);

	if (pFont == NULL)
		std::cout << "Failed to load font: " << TTF_GetError() << std::endl;

	SDL_Surface *textSurface = TTF_RenderText_Solid (pFont, mMessages[mIndex].c_str(), textColor);

	if (textSurface == NULL)
		std::cout << "Failed to make text surface: " << SDL_GetError() << std::endl;

	pText = SDL_CreateTextureFromSurface(ren->render, textSurface);
	rPositionText.x = 90;
	rPositionText.y = 570;
	rPositionText.w = textSurface->w;
	rPositionText.h = textSurface->h;

	SDL_FreeSurface(textSurface);

	SDL_Surface *titleSurface = TTF_RenderText_Solid(pFont, mTitles[mIndex].c_str(), textColor);

	if (titleSurface == NULL)
		std::cout << "Failed to make title surface: " << SDL_GetError() << std::endl;

	pTitle = SDL_CreateTextureFromSurface(ren->render, titleSurface);
	rPositionTitle.x = 20;
	rPositionTitle.y = 530;
	rPositionTitle.w = titleSurface->w;
	rPositionTitle.h = titleSurface->h;

	SDL_FreeSurface(titleSurface);

	tObjTex = LoadTexture ("./res/test_textbox.png");
	rPosition.x = 0;
	rPosition.y = 512;
	rPosition.w = 1366;
	rPosition.h = 256;
}

Textbox::~Textbox (void)
{
	//Clear things up
	mMessages.clear();
	mTitles.clear();

	//Should never be null but can never be too sure
	if (pFont)
		TTF_CloseFont(pFont);
	pFont = NULL;

	if (pText)
		SDL_DestroyTexture(pText);
	pText = NULL;

	if (pTitle)
		SDL_DestroyTexture(pTitle);
	pTitle = NULL;
}

void Textbox::Update (void) {}

void Textbox::Draw (void) 
{
	SDL_RenderCopy(ren->render, tObjTex, NULL, &rPosition);
	SDL_RenderCopy(ren->render, pTitle, NULL, &rPositionTitle);
	SDL_RenderCopy(ren->render, pText, NULL, &rPositionText);
}

bool Textbox::AdvanceText(void)
{
	//Set up some crap to allow for char-by-char drawing later
	return AdvanceTextInstant();
}

//Instantly advance the text to the next message
bool Textbox::AdvanceTextInstant (void)
{
	mIndex++;
	if (mIndex >= mMessages.size())
	{
		//Kill the textbox
		//Probably several globals to go and change later
		return false;
	}

	//Destroy the previous text
	SDL_DestroyTexture(pText);
	SDL_DestroyTexture(pTitle);
	
	//Change the message to render to the screen
	SDL_Surface *textSurface = TTF_RenderText_Solid(pFont, mMessages[mIndex].c_str(), textColor);

	//Error Checking
	if (textSurface == NULL)
	{
		std::cout << "Failed to make text surface: " << SDL_GetError() << std::endl;
		return false;
	}
	
	pText = SDL_CreateTextureFromSurface(ren->render, textSurface);
	rPositionText.w = textSurface->w;
	rPositionText.h = textSurface->h;

	SDL_FreeSurface(textSurface);
	
	//Change the title as well
	SDL_Surface *titleSurface = TTF_RenderText_Solid(pFont, mTitles[mIndex].c_str(), textColor);

	//Error Checking
	if (titleSurface == NULL)
	{
		std::cout << "Failed to make title surface: " << SDL_GetError() << std::endl;
		return false;
	}

	pTitle = SDL_CreateTextureFromSurface(ren->render, titleSurface);
	rPositionTitle.w = titleSurface->w;
	rPositionTitle.h = titleSurface->h;
	
	SDL_FreeSurface(titleSurface);

	return true;
}

//Need some options and a putchar() of some sort to add text one character at a time
//STATE MACHINE BITCHES