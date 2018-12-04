
#include "FallExplode.h"

#include "Body.h"
#include "Animator.h"
#include "Transform.h"
#include "../Managers/GameObject.h"
#include "../Managers/ObjectFactory.h"
#include "../Managers/Events.h"
#include "../Maths/Math2D.h"
#include "../Managers/Frame Rate Controller.h"

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
	mCurrDelay += gpFrameRateController->GetFrameTime();
	
	if (mCurrDelay > mDelayLimit && !Exploding)
	{
		Explode();
	}
}

void FallExplode::Serialize(JSONObject obj)
{
	mDelayLimit = (float)obj[L"Limit"]->AsNumber();
}

Component* FallExplode::Create()
{
	return new FallExplode();
}

void FallExplode::HandleEvent(Event * pEvent)
{
	if (pEvent->mType == WALLCOLLIDE)
	{
		WallCollideEvent *wc = static_cast<WallCollideEvent*>(pEvent);
		Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		Vector2D Pe;

		Vector2DScaleAdd(&Pe, &pBody->mVelocity, &pBody->mPosition, gpFrameRateController->GetFrameTime());
		Vector2D Rv, Pi;
		LineSegment2D Ls;
		Vector2D P0, P1;
		if (wc->side == 0)
		{
			Vector2DSet(&P0, 135.0f, 135.0f);
			Vector2DSet(&P1, 135.0f, 585.0f);
		}
		else if(wc->side == 1)
		{
			Vector2DSet(&P0, 135.0f, 585.0f);
			Vector2DSet(&P1, 825.0f, 585.0f);
		}
		else if (wc->side == 2)
		{
			Vector2DSet(&P0, 825.0f, 585.0f);
			Vector2DSet(&P1, 825.0f, 135.0f);
		}
		else
		{
			Vector2DSet(&P0, 135.0f, 135.0f);
			Vector2DSet(&P1, 825.0f, 135.0f);
		}
		BuildLineSegment2D(&Ls, &P0, &P1);
		float ti = ReflectAnimatedPointOnStaticLineSegment(&pBody->mPosition, &Pe, &Ls, &Pi, &Rv);

		
		if (ti != -1.0f)
		{
			Vector2DNormalize(&Rv, &Rv);
			Vector2DScale(&pBody->mVelocity, &Rv, GRENADE_SPEED);
		}
		
	}
}

void FallExplode::Explode()
{
	Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
	Vector2DZero(&pBody->mVelocity);
	Animator* pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
	Transform *pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
	Vector2DSet(&pTr->mScale, 200.0, 200.0);
	//ShapeAABB *rect = static_cast<ShapeAABB*>(pBody->mpShape);
	//rect->mTop = rect->mBottom = rect->mLeft = rect->mRight = 150.0f;
	ShapeCircle *circle = static_cast<ShapeCircle*>(pBody->mpShape);
	circle->mRadius = 75.0f;
	pAnimator->PlayAnimation("explode", true);
	Exploding = true;
}
