#include "GameStateManager.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "GameObjectManager.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "../Components/Body.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"

extern GameObjectManager *gpGameObjectManager;
extern ObjectFactory *gpObjectFactory;

GameStateManager::GameStateManager()
{

}

GameStateManager::~GameStateManager()
{

}

void GameStateManager::PrecacheLevels(const char* pFileName)
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
	JSONArray levels = root[L"Levels"]->AsArray();
	int type;
	for (unsigned int i = 0; i < levels.size(); ++i)
	{
		JSONObject obj = levels[i]->AsObject();

		//Type
		type = (int)obj[L"Level"]->AsNumber();

		//File
		std::wstring wt = obj[L"File"]->AsString();
		std::string FileName = std::string(wt.begin(), wt.end());

		std::string Path = "res/data/";
		Path += FileName;
		std::ifstream file(Path);
		std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		value = JSON::Parse(contents.c_str());
		if (value == NULL)
		{
			printf("value is null");
		}
		JSONObject *level = new JSONObject();
		*level = value->AsObject();
		mLevels[(Levels)type] = level;
	}
}

void GameStateManager::LoadLevel(Levels pLevelName)
{
	gpGameObjectManager->mGameObjects.erase(gpGameObjectManager->mGameObjects.begin(), gpGameObjectManager->mGameObjects.end());

	JSONObject root = *mLevels[pLevelName];
	JSONArray objects = root[L"Objects"]->AsArray();
	int type;
	
	for (unsigned int i = 0; i < objects.size(); ++i)
	{
		GameObject *pGameObject = nullptr;
		JSONObject obj = objects[i]->AsObject();

		if (obj.find(L"Type") != obj.end())
			type = (int)obj[L"Type"]->AsNumber();
		if (obj.find(L"File") != obj.end())
		{
			std::wstring wt = obj[L"File"]->AsString();
			std::string FileName = std::string(wt.begin(), wt.end());
			pGameObject = gpObjectFactory->LoadObject(FileName.c_str(), GameObjectTypes(type));
		}
		else
		{
			pGameObject = new GameObject(GameObjectTypes(type));
			gpGameObjectManager->mGameObjects.push_back(pGameObject);
		}

		if (obj.find(L"Body") != obj.end())
		{
			Body *pBody = static_cast<Body*>(pGameObject->AddComponent(BODY));
			if (pBody != nullptr)
				pBody->Serialize(obj[L"Body"]->AsObject());
		}

		if (obj.find(L"Transform") != obj.end())
		{
			Transform *pTr = static_cast<Transform*>(pGameObject->GetComponent(TRANSFORM));
			if (!pTr)
			{
				pTr = static_cast<Transform*>(pGameObject->AddComponent(TRANSFORM));
			}

			pTr->Serialize(obj[L"Transform"]->AsObject());
			if (type != NO_OBJECT)
			{
				Body *pBody = static_cast<Body*>(pGameObject->GetComponent(BODY));
				if (pBody != nullptr)
					pBody->Initialize();
			}
		}
		if (obj.find(L"Sprite") != obj.end())
		{
			Sprite *pSp = static_cast<Sprite*>(pGameObject->AddComponent(SPRITE));
			pSp->Serialize(obj[L"Sprite"]->AsObject());
		}
	}
}

