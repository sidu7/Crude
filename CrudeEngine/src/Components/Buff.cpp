/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Buff.cpp
Purpose:		Temporary Buff Effect on GameObject
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "Buff.h"
#include "../Managers/GameObject.h"
#include "../Managers/Frame Rate Controller.h"
#include "../Managers/GameObjectManager.h"

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