/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Spawner.cpp
Purpose:		Spawning waves of GameObjects after definite time interval
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "Spawner.h"
#include "../Managers/Frame Rate Controller.h"
#include "../Managers/ObjectFactory.h"
#include "../Managers/GameObject.h"
#include "Body.h"
#include "Transform.h"
#include "Animator.h"
#include "Drop.h"
#include <time.h>

extern FrameRateController *gpFrameRateController;
extern ObjectFactory *gpObjectFactory;

Spawner::Spawner() : Component(SPAWNER), mCurrDelay(0.0f)
{
	mStartDelay = mStatic;
	mStatic += 1.0f;
}

Spawner::~Spawner()
{
}

void Spawner::Update()
{
	mCurrDelay += gpFrameRateController->GetFrameTime();
	if (mCurrDelay > mStartDelay + 2.0f)
	{
		GameObject *pCrawler = gpObjectFactory->GetArcheType(GHOUL);
		Body *pTombBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		Body *pCrawlerBody = static_cast<Body*>(pCrawler->GetComponent(BODY));
		//---- Offset -----------
		if (mStartDelay == 0.0f)
			Vector2DSet(&pCrawlerBody->mPosition, pTombBody->mPosition.x + 50.0f, pTombBody->mPosition.y + 20.0f);
		else
			Vector2DSet(&pCrawlerBody->mPosition, pTombBody->mPosition.x - 50.0f, pTombBody->mPosition.y - 20.0f);
		//-------------------------
		mCurrDelay = mStartDelay;

		//------ Add Drop Items -----
		srand((unsigned int)time(NULL));
		int value = rand() % 20;
		if (value == 1 || value == 3 || value == 5 || value == 7)
		{
			Drop *pDrop = static_cast<Drop*>(pCrawler->AddComponent(DROP));
			pDrop->mType = DropType(value);
		}
	}
}

Component * Spawner::Create()
{
	return new Spawner();
}

void Spawner::HandleEvent(Event * pEvent)
{
}
