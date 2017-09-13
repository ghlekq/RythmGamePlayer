#pragma once

#include "GameObject.h"

class Sprite;

class Note : public GameObject
{
private:
	int _startTick;
	int _updateDuration;
	int _x;
	int _y;

	bool _isPass;
	bool _isLive;

public:
	Note(float sec, int judgeLineDelta,int x_width);
	~Note();

public:
	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();

	void UpdatePosition(int deltaTime);

	void Pass();
	bool IsPass();

	bool IsLive();
	int GetNoteTime();

	// Sprite
public:
	Sprite* _sprite;
	int _judgeLineDelta;
};