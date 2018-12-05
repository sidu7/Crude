/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Follow.cpp
Purpose:		Follow Component to follow a GameObject in scene
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "Follow.h"
#include "Transform.h"
#include "../Managers/GameObjectManager.h"
#include "../Managers/GameObject.h"
#include "Body.h"
#include "../Managers/Events.h"
#include "../Maths/Vector2D.h"


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
		Vector2DSet(&eDir, (float)cosf(PI), (float)sinf(PI));
		Vector2DNormalize(&Dir, &Dir);
		if(mpOwner->mType == CRAWLER)
			Vector2DScale(&mBody->mVelocity, &Dir, CRAWLER_VELOCITY);
		else
			Vector2DScale(&mBody->mVelocity, &Dir, GHOUL_VELOCITY);
		float ang = getAngleVector(Dir, eDir);
		if (ang > 0)
			mBody->mAngV = (float)acosf(Dir.x) * 180.0f / PI;
		else
			mBody->mAngV = (float)-(acosf(Dir.x) * 180 / PI);
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
