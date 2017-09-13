#include <stdio.h>

#include "ResourceManager.h"
#include "GameSystem.h"

using namespace std;

ResourceManager* ResourceManager::_instance = NULL;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	map<string, SDL_Texture*>::iterator it;
	for (it = _textureMap.begin(); it != _textureMap.end(); it++)
	{
		delete it->second;
	}
	_textureMap.clear();
}

// Singleton
ResourceManager* ResourceManager::GetInstance()
{
	if (NULL == _instance)
	{
		_instance = new ResourceManager();
	}
	return _instance;
}

SDL_Texture*  ResourceManager::FindTexture(string filePath)
{
	map<string, SDL_Texture*>::iterator it = _textureMap.find(filePath);
	if (it != _textureMap.end())
	{
		return it->second;//string�� ù���簪 SDL_texture*�� �ι�°��
	}
	SDL_Texture *texture = IMG_LoadTexture(GameSystem::GetInstance()->GetRenderer(), filePath.c_str());//c_str:const char���� �״�� ��ȯ���ش�
	_textureMap[filePath] = texture;

	return texture;
}