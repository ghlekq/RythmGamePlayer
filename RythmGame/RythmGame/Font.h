#pragma once

#include "Texture.h"

class Font : public Texture
{
private:
	TTF_Font* _sansfont;
public:
	Font(const char* fileName,int fontSize);
	~Font();

public:
	void SetText(const char* text);
};