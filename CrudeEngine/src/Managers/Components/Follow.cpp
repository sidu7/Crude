#include "Follow.h"
#include "Transform.h"
#include "../GameObjectManager.h"
#include "../GameObject.h"
#include "Body.h"
#include "../Events.h"
#include "../../Maths/Vector2D.h"


extern GameObjectManager *gpGameObjectManager;

Follow::Follow() : Component(FOLLOW), Init(false)
{	
}

Follow::~Follow()
{
}

void Follow::Initialize()
{
	for (auto g : gpGameObjectManager->mGameObjects)
		if (g->mType == PLAYER)
			mPlayerPos = static_cast<Transform*>(g->GetComponent(TRANSFORM));
}

void Follow::Update()
{
	Body *mBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
	if (mBody == nullptr)
		return;
	if (mPlayerPos != nullptr)
	{
		Vector2D Dir, eDir;
		Vector2DSub(&Dir, &mPlayerPos->mPosition, &mBody->mPosition);
		Vector2DSet(&eDir, cosf(PI), sinf(PI));
		Vector2DNormalize(&Dir, &Dir);
		if(mpOwner->mType == CRAWLER)
			Vector2DScale(&mBody->mVelocity, &Dir, CRAWLER_VELOCITY);
		else
			Vector2DScale(&mBody->mVelocity, &Dir, GHOUL_VELOCITY);
		float ang = getAngleVector(Dir, eDir);
		if (ang > 0)
			mBody->mAngV = acosf(Dir.x) * 180 / PI;
		else
			mBody->mAngV = -(acosf(Dir.x) * 180 / PI);
	}
	else
	{
		Vector2DZero(&mBody->mVelocity);
	}
}

Component* Follow::Create()
{
	return new Follow();
}

float Follow::getAngleVector(Vector2D mVec1, Vector2D aVec2)
{

	float dotProduct, angle;
	Vector2D UpVec;

	dotProduct = Vector2DDotProduct(&mVec1, &aVec2);
	Vector2DSet(&UpVec, -mVec1.y, mVec1.x);


	angle = acosf(dotProduct / (Vector2DLength(&mVec1)*Vector2DLength(&aVec2)));

	if (Vector2DDotProduct(&UpVec, &aVec2) < 0)
	{
		angle = -angle;
	}
	return angle;
}
