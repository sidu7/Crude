#include "Drop.h"
#include "../Managers/GameObject.h"
#include "../Managers/ObjectFactory.h"
#include "Transform.h"
#include "Sprite.h"
#include "Body.h"
#include "Buff.h"
#include "../Maths/Vector2D.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/GameObjectManager.h"

extern ResourceManager *gpResourceManager;
extern ObjectFactory *gpObjectFactory;
extern GameObjectManager *gpGameObjectManager;

Drop::Drop() : Component(DROP), Dropped(false)
{
}

Drop::~Drop()
{
}

void Drop::Update()
{
	if (mpOwner->Destroyed && !Dropped)
	{
 		Transform *pOwner = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
		GameObject *pDrop;
		Sprite* pSp = nullptr;
		if (mType == CRAWL)
		{
			pDrop = gpObjectFactory->GetArcheType(CRAWLER);
		}
		else
		{
			pDrop = gpObjectFactory->GetArcheType(DROPITEM);
			Buff *pBuff = static_cast<Buff*>(pDrop->AddComponent(BUFF));
			pBuff->DropType = mType;
			pBuff->BuffTime = 5.0f;
			pSp = static_cast<Sprite*>(pDrop->AddComponent(SPRITE));
		}
		Transform *pTr = static_cast<Transform*>(pDrop->GetComponent(TRANSFORM));
		Vector2DSet(&pTr->mPosition, pOwner->mPosition.x, pOwner->mPosition.y);
		Body *pBody = static_cast<Body*>(pDrop->GetComponent(BODY));
		pBody->Initialize();
		switch (mType)
		{
		case MEDKIT:
			pSp->mpTexture = gpResourceManager->LoadSurface("res/textures/drops/medkit.png");
			break;
		case DGRENADE:
			pSp->mpTexture = gpResourceManager->LoadSurface("res/textures/drops/grenade.png");
			break;
		case DOUBLEDMG:
			pSp->mpTexture = gpResourceManager->LoadSurface("res/textures/drops/doubledmg.png");
			break;
		}
		Dropped = true;
	}
}

Component * Drop::Create()
{
	return new Drop();
}
