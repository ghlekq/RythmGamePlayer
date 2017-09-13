#include <stdio.h>
#include "ResourceSystem.h"


// ������� ������ ���� ������� �ٽ� ��������߸�, �Ϲ� ��� ����ó�� ����� �� �ִ�.
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