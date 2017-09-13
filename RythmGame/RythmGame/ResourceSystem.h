#pragma once


class ResourceSystem
{
	// Singleton
private:
	static ResourceSystem* _instance;

public:
	static ResourceSystem& GetInstance();

private:
	ResourceSystem();		// 다른 곳에서 실수로 생성하지 않도록, 생성자를 프라이빗으로 만든다.

public:
	~ResourceSystem();

	void Init();
};
