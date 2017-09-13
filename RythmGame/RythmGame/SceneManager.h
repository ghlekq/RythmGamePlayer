#pragma once

struct Scene;
class SceneManager
{
private:
	static SceneManager* _instance;
	// Singleton
private:
	SceneManager();		// 다른 곳에서 실수로 생성하지 않도록, 생성자를 프라이빗으로 만든다.

public:
	~SceneManager();
private:
	Scene* _scene;

public:
	static SceneManager* GetInstance();
	void ChangeScene(const char* scenetitle);
	void KeyUp(int keycode);
	void KeyDown(int keycode);
	void Update(int deltaTime);
	void Render();


};