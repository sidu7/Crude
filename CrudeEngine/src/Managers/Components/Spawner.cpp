#include "Spawner.h"
#include "../Frame Rate Controller.h"
#include "../ObjectFactory.h"
#include "../GameObject.h"
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
		GameObject *pCrawler = gpObjectFactory->LoadObject("Ghoul.json", CRAWLER);
		Body *pTombBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		Body *pCrawlerBody = static_cast<Body*>(pCrawler->GetComponent(BODY));
		Transform *pCrawlerTrans = static_cast<Transform*>(pCrawler->GetComponent(TRANSFORM));
		//---- Offset -----------
		if (mStartDelay == 1.0f)
			Vector2DSet(&pCrawlerBody->mPosition, pTombBody->mPosition.x + 50.0f, pTombBody->mPosition.y + 20.0f);
		else
			Vector2DSet(&pCrawlerBody->mPosition, pTombBody->mPosition.x - 50.0f, pTombBody->mPosition.y - 20.0f);
		//-------------------------
		Vector2DSet(&pCrawlerTrans->mScale, 80.0f, 80.0f);
		mCurrDelay = mStartDelay;

		//------ Add Drop Items -----
		srand(time(NULL));
		int value = rand() % 20;
		if (value == 1 || value == 3 || value == 5)
		{
			Drop *pDrop = static_cast<Drop*>(pCrawler->AddComponent(DROP));
			pDrop->mType = DropType(value);
		}
		//---------------------------
	}
}

Component * Spawner::Create()
{
	return new Spawner();
}

void Spawner::HandleEvent(Event * pEvent)
{
}
