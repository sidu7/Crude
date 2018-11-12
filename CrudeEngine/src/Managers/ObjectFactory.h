#pragma once

class GameObject;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	void LoadLevel(const char *pFileName);
	GameObject* LoadObject(const char* pFileName, int type);
};
