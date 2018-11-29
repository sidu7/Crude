#include "Buff.h"
#include "../GameObject.h"
#include "../Frame Rate Controller.h"
#include "../GameObjectManager.h"

extern FrameRateController *gpFrameRateController;
extern GameObjectManager *gpGameObjectManager;


Buff::Buff() : Component(BUFF), BuffTime(0.0f)
{
}

Buff::~Buff()
{
}

void Buff::Update()
{
	BuffTime -= gpFrameRateController->GetFrameTime();
	if (BuffTime < 0.0f)
	{
		if (mpOwner->mType == PLAYER)
		{
			gpGameObjectManager->Destroy(Bufficon);
			mpOwner->RemoveComponent(BUFF);
		}
		else
			gpGameObjectManager->Destroy(mpOwner);
	}
}

Component * Buff::Create()
{
	return new Buff();
}