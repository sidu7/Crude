#include "Attributes.h"
#include "../Events.h"
#include "../GameObjectManager.h"

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
	mDamage = obj[L"Damage"]->AsNumber();
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
			gpGameObjectManager->Destroy(mpOwner);
		}
	}
}
