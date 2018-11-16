#include "FallExplode.h"

#include "Body.h"
#include "Animator.h"
#include "Transform.h"
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
		Transform *pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
		Vector2DSet(&pTr->mScale, 200.0, 200.0);
		ShapeAABB *rect = static_cast<ShapeAABB*>(pBody->mpShape);
		rect->mTop = rect->mBottom = rect->mLeft = rect->mRight = 150.0f;
		pAnimator->PlayAnimation("explode",true);
		Exploding = true;
	}
}

void FallExplode::Serialize(JSONObject obj)
{
	mDelayLimit = obj[L"Limit"]->AsNumber();
}

Component * FallExplode::Create()
{
	return new FallExplode();
}

void FallExplode::HandleEvent(Event * pEvent)
{
	
}

