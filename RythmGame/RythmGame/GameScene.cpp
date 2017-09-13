#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sdl.h"
#include "sdl_mixer.h"
#include "sdl_ttf.h"

#include "GameSystem.h"
#include "Sprite.h"
#include "Track.h"
#include "GameScene.h"
#include "Font.h"


GameScene::GameScene()
{
	_backgroundSprite = NULL;
	_textFont = NULL;
}

GameScene::~GameScene()
{
	Deinit();
}

void GameScene::Init()
{
	char filePath[256];
	sprintf(filePath, "../Resources/%s", "gameplay.csv");
	FILE* fp = fopen(filePath, "r");
	if (NULL == fp)
	{
		printf("File Open Error %s\n", filePath);
	}

	char backgroundSprName[256];
	char musicFileName[256];
	float gameTimeMin;

	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);
	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		{
			char* token = strtok(record, ",\n");
			if (!strcmp(token, "Background"))
			{
				token = strtok(NULL, ",\n");
				strcpy(backgroundSprName, token);
			}
			else if (!strcmp(token, "MusciName"))
			{
				token = strtok(NULL, ",\n");
				strcpy(musicFileName, token);
			}
			else if (!strcmp(token, "PlayTime"))
			{
				token = strtok(NULL, ",\n");
				gameTimeMin = atof(token);
			}
		}
	}

	int BPM = 120;
	int tempo = BPM / 60;

	float gameTime = 60.0f * gameTimeMin;
	int trackHeight = GameSystem::GetInstance()->GetWindowHeight() * (gameTime * tempo);
	trackHeight /= 2;
	GameSystem::GetInstance()->SetGameTime(gameTime);
	GameSystem::GetInstance()->SetTrackHeight(trackHeight);

	fclose(fp);

	_backgroundSprite = new Sprite(backgroundSprName, true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2);

	_trackleft = new Track(300, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_trackleft->Init();
	_trackup = new Track(500, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_trackup->Init();
	_trackright = new Track(700, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_trackright->Init();

	_gameDuration = 0;

	_textFont = new Font("arialbd.ttf",24);
	_textFont->SetPosition(50, 200);

	int result = Mix_Init(MIX_INIT_MP3);	
	if (MIX_INIT_MP3 == result)
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, gameTimeMin, 640);
		char musicFilePath[256];
		sprintf(musicFilePath, "../Resources/Music/%s", musicFileName);
		Mix_Music* music = Mix_LoadMUS(musicFilePath);
		if (NULL != music)
		{
			printf("Play Music\n");

			char text[256];
			sprintf(text, "Score:%d",GameSystem::GetInstance()->Score());
			_textFont->SetText(text);

			Mix_PlayMusic(music, 1);
		}
		else
		{
			printf("Error LoadMusic\n");
		}
	}
	else
	{
		printf("Error init MP3\n");
	}
}

void GameScene::Deinit()
{
	_trackleft->Deinit();
	_trackup->Deinit();
	_trackright->Deinit();
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}
	if (NULL != _textFont)
	{
		delete _textFont;
		_textFont = NULL;
	}
}

void GameScene::Update(int deltaTime)
{
	if(_gameDuration <= GameSystem::GetInstance()->GetGameTimeTick() + 2000)
	{
		_backgroundSprite->Update(deltaTime);
		_trackleft->Update(deltaTime);
		_trackup->Update(deltaTime);
		_trackright->Update(deltaTime);

		_gameDuration += deltaTime;
	}
	else
	{
		GameSystem::GetInstance()->Quit();
	}
}

void GameScene::Render()
{
	_backgroundSprite->Render();
	_trackleft->Render();
	_trackup->Render();
	_trackright->Render();

	_textFont->Render();
}


void GameScene::KeyDown(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_LEFT:
		_trackleft->KeyDown();
		break;
	case SDLK_UP:
		_trackup->KeyDown();
		break;
	case SDLK_RIGHT:
		_trackright->KeyDown();
		break;
	}
}

void GameScene::KeyUp(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_LEFT:
		_trackleft->KeyUp();
		break;
	case SDLK_UP:
		_trackup->KeyUp();
		break;
	case SDLK_RIGHT:
		_trackright->KeyUp();
		break;
	}
}
