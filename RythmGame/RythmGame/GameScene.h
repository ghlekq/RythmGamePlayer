#pragma once

#include "Scene.h"

class Sprite;
class Track;
class Font;
struct SDL_Texture;
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	
	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();

	// Input
public:
	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
	
	// Game
private:
	Sprite* _backgroundSprite;
	Track* _trackleft;
	Track* _trackup;
	Track* _trackright;
	int _gameDuration;
	SDL_Texture* _textTexture;
	int _score;
	//Font
	Font* _textFont;
};