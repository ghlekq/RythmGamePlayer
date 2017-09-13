#pragma once

#include "SDL.h"

class GameSystem
{
	// Singleton
private:
	static GameSystem* _instance;

public:
	static GameSystem* GetInstance();

private:
	GameSystem();		// �ٸ� ������ �Ǽ��� �������� �ʵ���, �����ڸ� �����̺����� �����.

public:
	~GameSystem();

	// Window Info
public:
	int GetWindowWidth();
	int GetWindowHeight();

	void Quit();


	// GameInfo
private:
	int _gameTimeTick;
	int _trackHeight;

public:
	void SetGameTime(float sec);
	int GetGameTimeTick();
	void SetTrackHeight(int height);
	int GetTrackHeight();


	// SDL
private:
	SDL_Renderer* _sdlRenderer;

public:
	void SetRender(SDL_Renderer* sdlRenderer);
	SDL_Renderer* GetRenderer();

private:
	int _score=0;
	int x_width=0;
	int _life = 1000;

public:
	int Score();
	void SetScore(int getscore);
	int Width();
	void SetWidth(int getwidth);
	int Life();
	void SetLife(int defaultlife);
};