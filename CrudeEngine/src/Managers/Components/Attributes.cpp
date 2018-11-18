#include "Attributes.h"
#include "../Events.h"
#include "../GameObjectManager.h"
#include "../GameObject.h"
#include "Animator.h"

extern GameObjectManager *gpGameObjectManager;

extern EventManager *gpEventManager;//to remove


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
			PlayerHitEvent *phe = new PlayerHitEvent();
			phe->HPLost = td->DamageDealt / 10.0f;
			gpEventManager->BroadcastEventToSubscribers(phe);
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
				pAnimator->PlayAnimation("die", false);
				mpOwner->RemoveComponent(BODY);
				mpOwner->RemoveComponent(ATTRIBUTES);
				mpOwner->RemoveComponent(FOLLOW);
				mpOwner->RemoveComponent(SUBSCRIPTION);
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
}
