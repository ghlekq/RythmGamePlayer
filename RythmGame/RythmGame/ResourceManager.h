#pragma once

#include <iostream>
#include <map>

#include "SDL_image.h"

class ResourceManager
{
private:
	static ResourceManager* _instance;
	// Singleton
private:
	ResourceManager();		// 다른 곳에서 실수로 생성하지 않도록, 생성자를 프라이빗으로 만든다.

public:
	~ResourceManager();

public:
	static ResourceManager* GetInstance();
	//Texture Resource
private:
	std::map<std::string, SDL_Texture*> _textureMap;
public:
	SDL_Texture* FindTexture(std::string filePath);
};