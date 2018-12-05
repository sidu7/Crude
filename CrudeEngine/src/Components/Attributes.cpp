/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Attributes.cpp
Purpose:		GameObject Attributes like HitPoints, Damage, etc.
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "Attributes.h"
#include "../Managers/Events.h"
#include "../Managers/GameObjectManager.h"
#include "../Managers/GameObject.h"
#include "Animator.h"
#include "Transform.h"
#include "Sprite.h"
#include "Buff.h"
#include "Body.h"

extern GameObjectManager *gpGameObjectManager;
extern int GrenadeCount;
extern EventManager *gpEventManager;
extern bool PlayerIsDead;
extern bool GodMode;


Attributes::Attributes() : Component(ATTRIBUTES), mCurrHP(0), mTotalHP(0), mDamage(0)
{
}

Attributes::~Attributes()
{
}

void Attributes::Update()
{
}

void Attributes::Serialize(JSONObject obj)
{
	mTotalHP = static_cast<int>(obj[L"TotalHP"]->AsNumber());
	if (obj.find(L"Damage") != obj.end())
	{
		mDamage = (int)obj[L"Damage"]->AsNumber();
	}
	mCurrHP = mTotalHP;
}

Component * Attributes::Create()
{
	return new Attributes;
}

void Attributes::HandleEvent(Event * pEvent)
{
	if (pEvent->mType == TAKEDAMAGE)
	{
		TakeDamage* td = static_cast<TakeDamage*>(pEvent);
		mCurrHP -= td->DamageDealt;
		if (mpOwner->mType == PLAYER)
		{
			if (!GodMode) {
				//Update Player HP bar
				PlayerHPEvent *phe = new PlayerHPEvent();
				phe->HPChange = -(td->DamageDealt*1.0f / mTotalHP);
				gpEventManager->BroadcastEventToSubscribers(phe);
				if (mCurrHP <= 0)
				{
					PlayerIsDead = true;
					gpGameObjectManager->Destroy(mpOwner);
				}
			}
		}
		if (mpOwner->mType == TOMBSTONE)
		{
			//Update Tombstone HP bar
			TombHitEvent *the = new TombHitEvent();
			the->HPLost = (td->DamageDealt*1.0f/mTotalHP);
			Transform *pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
			//find the tomb hit
			if (pTr->mPosition.x == 200.0f)
			{
				the->tomb = 1;
			}
			else
			{
				the->tomb = 2;
			}
			gpEventManager->BroadcastEventToSubscribers(the);
		}
		if (mCurrHP <= 0)
		{
			if (mpOwner->mType == TOMBSTONE)
			{
				Animator *pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
				pAnimator->PlayAnimation("destroy", false);
				mpOwner->RemoveComponent(BODY);
				mpOwner->RemoveComponent(SPAWNER);
			}
			else if (mpOwner->mType == GHOUL || mpOwner->mType == CRAWLER)
			{
				Animator *pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
				mpOwner->RemoveComponent(BODY);
				pAnimator->PlayAnimation("die", false);
			}
		}
	}
	else if (pEvent->mType == GRENADEHIT)
	{
		Animator *pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
		pAnimator->PlayAnimation("die", false);
		mpOwner->RemoveComponent(BODY);
		mpOwner->RemoveComponent(ATTRIBUTES);
		mpOwner->RemoveComponent(FOLLOW);
		mpOwner->RemoveComponent(SUBSCRIPTION);
	}
	else if (pEvent->mType == DROPPICKED)
	{
		DropPicked *dp = static_cast<DropPicked*>(pEvent);
		if (dp->Drop == MEDKIT)
		{
			if (mCurrHP < mTotalHP*0.9)
			{
				PlayerHPEvent *phe = new PlayerHPEvent();
				phe->HPChange = 0.1f;	
				gpEventManager->BroadcastEventToSubscribers(phe);
			}
		}
		else if (dp->Drop == DGRENADE)
		{
			if(GrenadeCount < 5)
				GrenadeCount++;
		}
		else if (dp->Drop == DOUBLEDMG)
		{
			GameObject *pBufficon = new GameObject(NO_OBJECT);
			pBufficon->AddComponent(TRANSFORM);
			pBufficon->AddComponent(SPRITE);
			pBufficon->SetTransform(500, SCREEN_HEIGHT - 30.0f, 40, 40, 0.0f);
			pBufficon->SetSprite("res/textures/doubledmg.png");
			gpGameObjectManager->mGameObjects.push_back(pBufficon);

			Buff *pBuff = static_cast<Buff*>(mpOwner->GetComponent(BUFF));
			if (pBuff == nullptr)
				pBuff = static_cast<Buff*>(mpOwner->AddComponent(BUFF));
			pBuff->BuffTime = 5.0f;
			pBuff->Bufficon = pBufficon;
		}
	}
}
