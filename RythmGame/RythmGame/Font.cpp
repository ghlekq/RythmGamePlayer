#include <stdio.h>

#include "sdl_ttf.h"

#include "Font.h"
#include "GameSystem.h"

Font::Font(const char* fileName, int fontSize)
{

	char filePath[256];
	sprintf(filePath, "../Resources/Font/%s", fileName);

	_sansfont = TTF_OpenFont(filePath, fontSize);
}

Font::~Font()
{

}

void Font::SetText(const char* text)
{
	SDL_Color black = { 0,0,0 };
	SDL_Surface* surfacemessage = TTF_RenderText_Solid(_sansfont, text, black);
	_texture = SDL_CreateTextureFromSurface(GameSystem::GetInstance()->GetRenderer(), surfacemessage);


	SDL_QueryTexture(_texture, NULL, NULL, &_srcRect.w, &_srcRect.h);

	_srcRect.x = 0;
	_srcRect.y = 0;

	_destRect.w = _srcRect.w;
	_destRect.h = _srcRect.h;

}