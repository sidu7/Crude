#include "PhysicsManager.h"
#include "Components/Body.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Events.h"

#include "../Defines.h"

extern GameObjectManager *gpGameObjectManager;
extern CollisionManager *gpCollisionManager;

#define GO gpGameObjectManager->mGameObjects

PhysicsManager::PhysicsManager()
{
}
PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Update(float FrameTime)
{
	
	for (auto go : gpGameObjectManager->mGameObjects)
	{
		Body *pBody = static_cast<Body*>(go->GetComponent(BODY));
		if (pBody != nullptr)
			pBody->Integrate(0.0, FrameTime);
	}

	//Reset previous contacts
	gpCollisionManager->Reset();

	//Check for intersections

	for (int pObj1 = 0; pObj1 < GO.size(); ++pObj1)
	{
		if (GO[pObj1]->mType == NO_OBJECT)
		{
			continue;
		}

		Body *pBody1 = static_cast<Body*>(GO[pObj1]->GetComponent(BODY));

		if (pBody1 == nullptr)
			continue;

		for (int pObj2 = pObj1 + 1; pObj2 < GO.size(); ++pObj2)
		{
			if (GO[pObj2]->mType == NO_OBJECT)
			{
				continue;
			}

			Body *pBody2 = static_cast<Body*>(GO[pObj2]->GetComponent(BODY));

			if (pBody2 == nullptr)
				continue;

			gpCollisionManager->checkCollisionAndGenerateContact(pBody1->mpShape, pBody1->mPosition.x, pBody1->mPosition.y,
				pBody2->mpShape, pBody2->mPosition.x, pBody2->mPosition.y, gpCollisionManager->mContacts);
		}
	}

	//Super Advanced Physics here!!!
	for (auto c : gpCollisionManager->mContacts)
	{
		if (c->mBodies[0]->mpOwner->mType == CRAWLER && c->mBodies[1]->mpOwner->mType == BULLET)
		{
			BulletHitEvent bh;
			c->mBodies[0]->mpOwner->HandleEvent(&bh);
			c->mBodies[1]->mpOwner->HandleEvent(&bh);
		}
		else if (c->mBodies[0]->mpOwner->mType == PLAYER && c->mBodies[1]->mpOwner->mType == WALL)
		{
			WallCollideEvent wc;
			c->mBodies[0]->mpOwner->HandleEvent(&wc);
		}
	}
}