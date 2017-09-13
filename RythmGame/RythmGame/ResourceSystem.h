#pragma once


class ResourceSystem
{
	// Singleton
private:
	static ResourceSystem* _instance;

public:
	static ResourceSystem& GetInstance();

private:
	ResourceSystem();		// �ٸ� ������ �Ǽ��� �������� �ʵ���, �����ڸ� �����̺����� �����.

public:
	~ResourceSystem();

	void Init();
};
