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
	ResourceManager();		// �ٸ� ������ �Ǽ��� �������� �ʵ���, �����ڸ� �����̺����� �����.

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