#include "GameObjectManager.h"
#include "GameObject.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "Components/Controller.h"
#include "Components/Body.h"
#include "Components/Animator.h"
#include "Components/Component.h"
#include "Components/Follow.h"

#include "../Defines.h"
GameObjectManager::GameObjectManager()
{
	mComponentMap[TRANSFORM] = new Transform();
	mComponentMap[SPRITE] = new Sprite();
	mComponentMap[CONTROLLER] = new Controller();
	mComponentMap[BODY] = new Body();
	mComponentMap[ANIMATOR] = new Animator();
	mComponentMap[FOLLOW] = new Follow();
}

GameObjectManager::~GameObjectManager()
{
	for (auto go : mGameObjects)
	{
		delete go;
	}
	mGameObjects.clear();
}

void GameObjectManager::Destroy(int itr)
{
	mGameObjects[itr]->~GameObject();
	std::vector<GameObject*>::iterator it = mGameObjects.begin() + itr;
	mGameObjects.erase(it);
}