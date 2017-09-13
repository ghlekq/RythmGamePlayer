#pragma once

#include "Array.h"

class Texture;

class Sprite
{
private:
	Array<Texture*>* _textureFrames;
	int _frames;
	int _frame;

	int _animationSpeed;
	int _frameDuration;

	int _x;
	int _y;

	bool _isLoop;
	bool _isPlay;

public:
	Sprite(const char* fileName, bool isLoop);
	~Sprite();

	void Update(int deltaTime);
	void Render();

	void SetPosition(int x, int y);

	void Play();
};