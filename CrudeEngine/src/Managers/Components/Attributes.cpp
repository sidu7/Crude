#include "Attributes.h"
#include "../Events.h"
#include "../GameObjectManager.h"
#include "../GameObject.h"
#include "Animator.h"
#include "Buff.h"

extern GameObjectManager *gpGameObjectManager;
extern int GrenadeCount;
extern EventManager *gpEventManager;
extern bool PlayerIsDead;


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
		mDamage = obj[L"Damage"]->AsNumber();
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
			PlayerHPEvent *phe = new PlayerHPEvent();
			phe->HPChange = -td->DamageDealt / 10.0f;
			gpEventManager->BroadcastEventToSubscribers(phe);
			if (mCurrHP == 0)
			{
				PlayerIsDead = true;
				gpGameObjectManager->Destroy(mpOwner);
			}
		}
		if (mCurrHP == 0)
		{
			if (mpOwner->mType == TOMBSTONE)
			{
				Animator *pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
				pAnimator->PlayAnimation("destroy", false);
				mpOwner->RemoveComponent(BODY);
				mpOwner->RemoveComponent(SPAWNER);
			}
			else if (mpOwner->mType == CRAWLER)
			{
				Animator *pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
				mpOwner->RemoveComponent(BODY);
				pAnimator->PlayAnimation("die", false);
			}
		}
	}
	if (pEvent->mType == GRENADEHIT)
	{
		Animator *pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
		pAnimator->PlayAnimation("die", false);
		mpOwner->RemoveComponent(BODY);
		mpOwner->RemoveComponent(ATTRIBUTES);
		mpOwner->RemoveComponent(FOLLOW);
		mpOwner->RemoveComponent(SUBSCRIPTION);
	}
	if (pEvent->mType == DROPPICKED)
	{
		DropPicked *dp = static_cast<DropPicked*>(pEvent);
		if (dp->Drop == MEDKIT)
		{
			PlayerHPEvent *phe = new PlayerHPEvent();
			phe->HPChange = 1.0f;
			gpEventManager->BroadcastEventToSubscribers(phe);
		}
		else if (dp->Drop == DGRENADE)
		{
			if(GrenadeCount < 5)
				GrenadeCount++;
		}
		else if (dp->Drop == DOUBLEDMG)
		{
			Buff *pBuff = static_cast<Buff*>(mpOwner->GetComponent(BUFF));
			if (pBuff == nullptr)
				pBuff = static_cast<Buff*>(mpOwner->AddComponent(BUFF));
			pBuff->BuffTime = 5.0f;
		}
	}
}
