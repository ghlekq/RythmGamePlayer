#pragma once
#include "GameObject.h"
class Sprite;
class Track;
class Font;

class Scene :public GameObject
{
public:
	Scene();
	~Scene();

	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();

		// Input
	public:
		virtual void KeyDown(int keyCode);
		virtual void KeyUp(int keyCode);
};