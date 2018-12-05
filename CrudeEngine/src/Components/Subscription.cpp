/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Subscription.cpp
Purpose:		Component that Subscribes to Events for a GameObject
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "Subscription.h"
#include "../Managers/Events.h"

extern EventManager *gpEventManager;


Subscription::Subscription() : Component(SUBSCRIPTION)
{
}

Subscription::~Subscription()
{
	for (unsigned int i = 0; i < mEventSubscriptions.size(); ++i)
	{
		gpEventManager->Unsubscribe(EventType(mEventSubscriptions[i]), mpOwner);
	}
}

void Subscription::Update()
{
}

void Subscription::Serialize(JSONObject obj)
{
	JSONArray events = obj[L"Events"]->AsArray();
	for (int i = 0; i < (int)events.size(); ++i)
	{	
		unsigned int type = (unsigned int)events[i]->AsNumber();
		gpEventManager->Subscribe(EventType(type), mpOwner);
		mEventSubscriptions.push_back(type);
	}
}

Component * Subscription::Create()
{
	return new Subscription();
}
