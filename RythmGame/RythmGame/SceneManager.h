#pragma once

struct Scene;
class SceneManager
{
private:
	static SceneManager* _instance;
	// Singleton
private:
	SceneManager();		// �ٸ� ������ �Ǽ��� �������� �ʵ���, �����ڸ� �����̺����� �����.

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