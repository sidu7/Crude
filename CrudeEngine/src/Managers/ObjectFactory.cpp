
#include "ObjectFactory.h"
#include "GameObject.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "GameObjectManager.h"
#include "Components/Body.h"
#include "Components/Follow.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../Defines.h"



extern GameObjectManager *gpGameObjectManager;

ObjectFactory::ObjectFactory()
{

}

ObjectFactory::~ObjectFactory()
{

}

void ObjectFactory::LoadArchetypes(const char *pFileName)
{
	std::string fullPath = "res/data/";
	fullPath += pFileName;
	std::ifstream file(fullPath);
	std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	JSONValue *value = JSON::Parse(contents.c_str());
	if (value == NULL)
	{
		printf("value is null");
	}
	JSONObject root = value->AsObject();
	JSONArray prefabs = root[L"Prefabs"]->AsArray();
	GameObjectTypes type;
	std::string FileName;
	GameObject *pGameObject = nullptr;
	for (unsigned int i = 0; i < prefabs.size(); ++i)
	{
		JSONObject obj = prefabs[i]->AsObject();
		//Type
		std::wstring wt = obj[L"Type"]->AsString();
		std::string tt(wt.begin(), wt.end());
		if ("Bullet" == tt)
			type = BULLET;
		else if ("Ghoul" == tt)
			type = GHOUL;
		else if ("Crawler" == tt)
			type = CRAWLER;
		else if ("Grenade" == tt)
			type = GRENADE;
		else if ("Drop" == tt)
			type = DROPITEM;
		//File
		wt = obj[L"File"]->AsString();
		FileName = std::string(wt.begin(), wt.end());
		
		std::string Path = "res/data/";
		Path += FileName;
		std::ifstream file(Path);
		std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		JSONValue *value = JSON::Parse(contents.c_str());
		if (value == NULL)
		{
			printf("value is null");
		}
		JSONObject *prefab = new JSONObject();
		*prefab = value->AsObject();
		mArchetypes[type] = prefab;
	}
}

void ObjectFactory::LoadLevel(const char *pFileName)
{

	std::string fullPath = "res/data/";
	fullPath += pFileName;
	std::ifstream file(fullPath);
	std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	JSONValue *value = JSON::Parse(contents.c_str());
	if (value == NULL)
	{
		printf("value is null");
	}
	JSONObject root = value->AsObject();
	JSONArray objects = root[L"Objects"]->AsArray();
	int type;
	std::string FileName;
	for (unsigned int i = 0; i < objects.size(); ++i)
	{
		JSONObject obj = objects[i]->AsObject();
		if (obj.find(L"File") != obj.end())
		{
			std::wstring wt = obj[L"File"]->AsString();
			FileName = std::string(wt.begin(), wt.end());
		}
		else
		{
			FileName = "";
		}
		if (obj.find(L"Type") != obj.end())
		{
			std::wstring wt = obj[L"Type"]->AsString();
			std::string tt(wt.begin(), wt.end());
			if ("Player" == tt)
				type = PLAYER;
			else if ("Wall" == tt)
				type = WALL;
			else if ("Tombstone" == tt)
				type = TOMBSTONE;
			else
				type = NO_OBJECT;

		}
		GameObject *pGameObject = nullptr;
		if (FileName == "")
		{
			pGameObject = new GameObject(GameObjectTypes(type));
			gpGameObjectManager->mGameObjects.push_back(pGameObject);
		}
		else
			pGameObject = LoadObject(FileName.c_str(), GameObjectTypes(type));

		if (obj.find(L"Body") != obj.end()){
			Body *pBody = static_cast<Body*>(pGameObject->GetComponent(BODY));
			if (!pBody)
			{
				pBody = static_cast<Body*>(pGameObject->AddComponent(BODY));
			}
			pBody->Serialize(obj[L"Body"]->AsObject());
		}
		if (obj.find(L"Transform") != obj.end()) {
			Transform *pTr = static_cast<Transform*>(pGameObject->GetComponent(TRANSFORM));
			if (!pTr)
			{
				pTr = static_cast<Transform*>(pGameObject->AddComponent(TRANSFORM));
			}

			pTr->Serialize(obj[L"Transform"]->AsObject());
			if (type != NO_OBJECT)
			{
				Body *pBody = static_cast<Body*>(pGameObject->GetComponent(BODY));
				pBody->Initialize();
			}
		}
		if (obj.find(L"Sprite") != obj.end()) {
			Sprite *pSp = static_cast<Sprite*>(pGameObject->AddComponent(SPRITE));
			pSp->Serialize(obj[L"Sprite"]->AsObject());
		}
	}


}

GameObject* ObjectFactory::LoadObject(const char *pFileName, GameObjectTypes type)
{
	GameObject *pNewGameObject = nullptr;
	
	std::string fullPath = "res/data/";
	fullPath += pFileName;
	std::ifstream file(fullPath);
	std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	JSONValue *value = JSON::Parse(contents.c_str());

	if (value->IsObject()) {

		Component *pNewComponent = nullptr;

		JSONObject root = value->AsObject();
		pNewGameObject = LoadObject(root, type);

		return pNewGameObject;
	}
}

GameObject* ObjectFactory::LoadObject(JSONObject root,GameObjectTypes type)
{

	GameObject *pNewGameObject = new GameObject(type);
	Component *pNewComponent = nullptr;

	if (root.find(L"Transform") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(TRANSFORM);
		pNewComponent->Serialize(root[L"Transform"]->AsObject());
	}
	if (root.find(L"Controller") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(CONTROLLER);
	}
	if (root.find(L"Body") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(BODY);
		pNewComponent->Serialize(root[L"Body"]->AsObject());
	}
	if (root.find(L"Animator") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(ANIMATOR);
		pNewComponent->Serialize(root[L"Animator"]->AsObject());
	}
	if (root.find(L"Follow") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(FOLLOW);
		Follow *pFollow = static_cast<Follow*>(pNewComponent);
		pFollow->Initialize();
	}
	if (root.find(L"FallExplode") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(FALLEXPLODE);
		pNewComponent->Serialize(root[L"FallExplode"]->AsObject());
	}
	if (root.find(L"Subscriptions") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(SUBSCRIPTION);
		pNewComponent->Serialize(root[L"Subscriptions"]->AsObject());
	}
	if (root.find(L"Spawner") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(SPAWNER);
	}
	if (root.find(L"Attributes") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(ATTRIBUTES);
		pNewComponent->Serialize(root[L"Attributes"]->AsObject());
	}
	if (root.find(L"Sprite") != root.end())
	{
		pNewComponent = pNewGameObject->AddComponent(SPRITE);
		pNewComponent->Serialize(root[L"Sprite"]->AsObject());
	}
	gpGameObjectManager->mGameObjects.push_back(pNewGameObject);

	return pNewGameObject;
}

GameObject* ObjectFactory::GetArcheType(GameObjectTypes type)
{
	return LoadObject(*mArchetypes[type],type);
}


