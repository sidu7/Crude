#include "Attributes.h"
#include "../Events.h"
#include "../GameObjectManager.h"
#include "../GameObject.h"
#include "Animator.h"

extern GameObjectManager *gpGameObjectManager;


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
	mTotalHP = obj[L"TotalHP"]->AsNumber();
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
		if (mCurrHP == 0)
		{
			if (mpOwner->mType == TOMBSTONE)
			{
				Animator *pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
				pAnimator->PlayAnimation("destroy", true);
			}
			else
				gpGameObjectManager->Destroy(mpOwner);
		}
	}
}
