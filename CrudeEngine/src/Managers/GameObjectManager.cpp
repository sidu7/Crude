#include "GameObjectManager.h"
#include "GameObject.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "Components/Controller.h"
#include "Components/Body.h"
#include "Components/Animator.h"
#include "Components/Component.h"
#include "Components/Follow.h"
#include "Components/FallExplode.h"
#include "Components/Subscription.h"
#include "Components/Spawner.h"
#include "Components/Attributes.h"

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
}

GameObjectManager::~GameObjectManager()
{
	for (auto go : mGameObjects)
	{
		delete go;
	}
	mGameObjects.clear();
}

void GameObjectManager::Destroy(GameObject* pGameObject)
{
	for (int i = 0; i < mGameObjects.size(); ++i)
		if (mGameObjects[i] == pGameObject)
		{
			//mGameObjects[i]->~GameObject();
			mGameObjects.erase(mGameObjects.begin()+i);
		}
}