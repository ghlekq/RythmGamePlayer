#include <stdio.h>
#include "ResourceSystem.h"


// 헤더에서 선언한 정적 멤버들을 다시 선언해줘야만, 일반 멤버 변수처럼 사용할 수 있다.
ResourceSystem* ResourceSystem::_instance = NULL;

ResourceSystem::ResourceSystem()
{
}

ResourceSystem::~ResourceSystem()
{

}

// Singleton
ResourceSystem& ResourceSystem::GetInstance()
{
	if (NULL == _instance)
	{
		_instance = new ResourceSystem();
	}
	return *_instance;
}

void ResourceSystem::Init()
{
}