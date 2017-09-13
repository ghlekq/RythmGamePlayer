#pragma once
#include "Scene.h"
class Sprite;
class Track;
class Font;

class TitleScene :public Scene
{
public:
	TitleScene();
	~TitleScene();
	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();
};
