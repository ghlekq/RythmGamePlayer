#include <stdio.h>


#include "SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"

SceneManager* SceneManager::_instance = NULL;

SceneManager::SceneManager()
{
	_scene = NULL;
}

SceneManager::~SceneManager()
{
	if (NULL != _scene)
	{
		_scene->Deinit();
		delete _scene;
	}
	
}

//Singleton
SceneManager* SceneManager::GetInstance()
{
	if (NULL == _instance)
	{
		_instance = new SceneManager();
	}
	return _instance;
}

void SceneManager::ChangeScene(const char* scenetitle)
{
	if (NULL != _scene)
	{
		_scene->Deinit();
		delete _scene;
	}

	switch (true)
	{
	default:
		break;
	}
	_scene = new GameScene();
	_scene->Init();
}

void SceneManager::KeyUp(int keycode)
{
	_scene->KeyUp(keycode);
}

void SceneManager::KeyDown(int keycode)
{
	_scene->KeyDown(keycode);
}

void SceneManager::Update(int deltaTime)
{
	_scene->Update(deltaTime);
}

void SceneManager::Render()
{
	_scene->Render();
}
