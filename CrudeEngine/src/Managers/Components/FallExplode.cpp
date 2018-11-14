#include "FallExplode.h"

#include "Body.h"
#include "Animator.h"
#include "../GameObject.h"
#include "../ObjectFactory.h"
#include "../Events.h"
#include "../Frame Rate Controller.h"

extern FrameRateController *gpFrameRateController;
extern EventManager *gpEventManager;
extern ObjectFactory *gpObjectFactory;

FallExplode::FallExplode() : Component(FALLEXPLODE), mCurrDelay(0.0f), Exploding(false), mDelayLimit(0.0f)
{
}


FallExplode::~FallExplode()
{
	gpEventManager->Unsubscribe(GRENADETHROW, mpOwner);
}

void FallExplode::Update()
{
	Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
	mCurrDelay += gpFrameRateController->GetFrameTime();
	
	if (mCurrDelay > mDelayLimit && !Exploding)
	{
		Vector2DZero(&pBody->mVelocity);
		Animator* pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
		pAnimator->PlayAnimation("explode",true);
		Exploding = true;
	}
}

void FallExplode::Serialize(JSONObject obj)
{
	mDelayLimit = obj[L"Limit"]->AsNumber();
	if (obj[L"Throw"]->AsBool())
	{
		gpEventManager->Subscribe(GRENADETHROW, mpOwner);
	}
}

Component * FallExplode::Create()
{
	return new FallExplode();
}

void FallExplode::HandleEvent(Event * pEvent)
{
	if (pEvent->mType == GRENADETHROW)
	{
		ThrowGrenadeEvent *tge = static_cast<ThrowGrenadeEvent*>(pEvent);
		GameObject *pGrenade = gpObjectFactory->LoadObject("grenade.json", GRENADE);
		Body *pGrenadeBody = static_cast<Body*>(pGrenade->GetComponent(BODY));
		printf("grenade");
		//---- Offset -----------
		Vector2D Offset;
		Vector2DSet(&Offset, 40.0f * cosf(tge->pBody->mAngV * PI / 180), 40.0f * sinf(tge->pBody->mAngV * PI / 180));
		//Vector2DSet(&Offset, 300.0 * cosf(pBody->mAngV * PI / 180), 300.0f * sinf(pBody->mAngV * PI / 180));
		Vector2DAdd(&pGrenadeBody->mPosition, &tge->pBody->mPosition, &Offset);
		//-------------------------

		pGrenadeBody->mAngV = tge->pBody->mAngV;
		//Animator *pGrenadeAnimator = static_cast<Animator*>(pGrenade->GetComponent(ANIMATOR));
		//pGrenadeAnimator->PlayAnimation("explode", true);
		pGrenadeBody->AddVelocity(GRENADE_SPEED);


	}
}

