#include "Body.h"
#include "../Managers/GameObject.h"
#include "Transform.h"
#include "../Managers/EventManager.h"
#include "../Managers/Events.h"
#include "../Managers/GameObjectManager.h"
#include "../Defines.h"

extern GameObjectManager *gpGameObjectManager;

Body::Body() : Component(BODY)
{
	mTotalForce.x = mTotalForce.y = 0.0f;
	mVelocity.x = mVelocity.y = 0.0f;
	mAngV = 0.0f;
}

Body::~Body()
{

}

void Body::Update()
{
}

void Body::Serialize(JSONObject obj)
{
	if (obj.find(L"Mass") != obj.end())
	{
		mMass = (float)obj[L"Mass"]->AsNumber();
		if (mMass != 0.0f)
		{
			mInvMass = 1.0f / mMass;
		}
		else
		{
			mInvMass = 0.0f;
		}
	}
	if (obj.find(L"Circle") != obj.end())
	{
		mpShape = new ShapeCircle((float)obj[L"Circle"]->AsNumber());
		mpShape->mpOwnerBody = this;
	}
	if (obj.find(L"AABB") != obj.end())
	{
		JSONArray coords = obj[L"AABB"]->AsArray();
		mpShape = new ShapeAABB((float)coords[0]->AsNumber(), (float)coords[1]->AsNumber(),(float)coords[2]->AsNumber(), (float)coords[3]->AsNumber());
		mpShape->mpOwnerBody = this;
	}
}


void Body::Initialize()
{
	Transform *pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));

	if (pTr != nullptr)
	{
		mPrevPosition.x = mPosition.x = pTr->mPosition.x;
		mPrevPosition.y = mPosition.y = pTr->mPosition.y;
		mAngV = pTr->mAngle;
	}
}

void Body::Integrate(float Gravity, float DeltaTime)
{
	//Save current position
	mPrevPosition.x = mPosition.x;
	mPrevPosition.y = mPosition.y;

	/*
	//Compute Acceleration
	mTotalForceY += Gravity;
	mAccX = mTotalForceX * mInvMass;
	mAccY = mTotalForceY * mInvMass;

	//Integrate the velocity
	mVelX = mAccX * DeltaTime + mVelX;
	mVelY = mAccY * DeltaTime + mVelY;
	*/

	//Integrate the position
	Vector2DScaleAdd(&mPosition, &mVelocity, &mPrevPosition, DeltaTime);
	//mPosX = mVelX * DeltaTime + mPosX;
	//mPosY = mVelY * DeltaTime + mPosY;

	//mTotalForce.x = mTotalForce.y = 0.0f;
	//mVelocity.x = mVelocity.y = 0.0f;

	Transform *pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));

	if (pTr != nullptr)
	{
		pTr->mPosition.x = mPosition.x;
		pTr->mPosition.y = mPosition.y;

		pTr->mAngle = mAngV;
	}
}

void Body::AddVelocity(float velocity)
{
	Vector2D vel;
	Vector2DSet(&vel, (float)cosf(mAngV*PI/180), (float)sinf(mAngV*PI/180));
	Vector2DScale(&mVelocity, &vel, velocity);
}

void Body::HandleEvent(Event * pEvent)
{
}

Component * Body::Create()
{
	return new Body();
}
