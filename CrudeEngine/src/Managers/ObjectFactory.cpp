/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		ObjectFactory.cpp
Purpose:		Create GameObjects by Serializing from Files
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/


#include "ObjectFactory.h"
#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"
#include "GameObjectManager.h"
#include "../Components/Body.h"
#include "../Components/Follow.h"

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
	int type;
	std::string FileName;
	GameObject *pGameObject = nullptr;
	for (unsigned int i = 0; i < prefabs.size(); ++i)
	{
		JSONObject obj = prefabs[i]->AsObject();
		//Type
		type = (int)obj[L"Type"]->AsNumber();

		//File
		std::wstring wt = obj[L"File"]->AsString();
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
		mArchetypes[(GameObjectTypes)type] = prefab;
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
	return nullptr;
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

