#pragma once
#include <map>
#include "../vendor/simplejson/JSON.h"

class GameObject;
enum GameObjectTypes;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	void LoadArchetypes(const char *pFileName);
	void LoadLevel(const char *pFileName);
	GameObject* LoadObject(const char* pFileName, GameObjectTypes type);
	GameObject* LoadObject(JSONObject obj, GameObjectTypes type);
	GameObject* GetArcheType(GameObjectTypes type);

private:
	std::map<GameObjectTypes,JSONObject*> mArchetypes;
};
