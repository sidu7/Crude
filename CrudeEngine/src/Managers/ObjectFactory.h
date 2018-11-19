#pragma once

class GameObject;
enum GameObjectTypes;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	void LoadLevel(const char *pFileName);
	GameObject* LoadObject(const char* pFileName, GameObjectTypes type);
};
