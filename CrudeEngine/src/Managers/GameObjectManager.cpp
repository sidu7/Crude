/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		GameObjectManager.cpp
Purpose:		Manages current GameObjects in the scene
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "GameObjectManager.h"
#include "GameObject.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../Components/Controller.h"
#include "../Components/Body.h"
#include "../Components/Animator.h"
#include "../Components/Component.h"
#include "../Components/Follow.h"
#include "../Components/FallExplode.h"
#include "../Components/Subscription.h"
#include "../Components/Spawner.h"
#include "../Components/Attributes.h"
#include "../Components/Drop.h"
#include "../Components/Buff.h"

#include "../Defines.h"
GameObjectManager::GameObjectManager()
{
	mComponentMap[TRANSFORM] = new Transform();
	mComponentMap[SPRITE] = new Sprite();
	mComponentMap[CONTROLLER] = new Controller();
	mComponentMap[BODY] = new Body();
	mComponentMap[ANIMATOR] = new Animator();
	mComponentMap[FOLLOW] = new Follow();
	mComponentMap[FALLEXPLODE] = new FallExplode();
	mComponentMap[SUBSCRIPTION] = new Subscription();
	mComponentMap[SPAWNER] = new Spawner();
	mComponentMap[ATTRIBUTES] = new Attributes();
	mComponentMap[DROP] = new Drop();
	mComponentMap[BUFF] = new Buff();
}

GameObjectManager::~GameObjectManager()
{
	for (auto go : mGameObjects)
	{
		delete go;
	}
	mGameObjects.clear();

	for (auto go : mStaticDeadObjects)
	{
		delete go;
	}
	mStaticDeadObjects.clear();
}


void GameObjectManager::Destroy(GameObject* pGameObject)
{
	for (unsigned int i = 0; i < mGameObjects.size(); ++i)
		if (mGameObjects[i] == pGameObject)
		{
			mGameObjects[i]->Destroyed = true;
			mDeleteObjects.push_back(pGameObject);
			mGameObjects.erase(mGameObjects.begin()+i);
		}
}

void GameObjectManager::Update()
{
	for (unsigned int i = 0; i < mDeleteObjects.size(); ++i)
	{
		delete mDeleteObjects[i];
	}
	mDeleteObjects.erase(mDeleteObjects.begin(), mDeleteObjects.end());
}

void GameObjectManager::MoveToStaticDead(GameObject* pGameObject)
{
	for (unsigned int i = 0; i < mGameObjects.size(); ++i)
		if (mGameObjects[i] == pGameObject)
		{
			mGameObjects[i]->Destroyed = true;
			mStaticDeadObjects.push_back(pGameObject);
			mGameObjects.erase(mGameObjects.begin() + i);
		}
}