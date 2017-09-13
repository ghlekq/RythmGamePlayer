#pragma once

#include "GameObject.h"
#include "DLinkedList.h"
#include "Array.h"

class Sprite;
class Note;

enum eJudge
{
	NONE,
	JUDGE,
	FAIL,
};


class Track : public GameObject
{
public:
	enum eEffect
	{
		EXPLOSION,
		FAIL,
	};

public:
	Track(int x,int y);
	~Track();

	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();

	// Input
private:
	bool _isKeyDown;

public:
	void KeyDown();
	void KeyUp();
private:
	DLinkedList<Sprite*> _backgroundSpriteList;
	DLinkedList<Note*> _noteList;

	Array<Sprite*>* _effectList;
	//Sprite* _explosionSprite;
	//Sprite* _failSprite;

	int _judgeLineDeltaPos;
	int _judgeStartTick;
	int _judgeEndTick;
	eJudge _judge;
	int y_height;

};