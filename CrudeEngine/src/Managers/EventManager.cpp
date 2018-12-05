/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		EventManager.cpp
Purpose:		Event Handling Manager
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "EventManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"

extern GameObjectManager *gpGameObjectManager;


Event::Event(EventType Type) : mType(Type), mTimer(0.0f)
{
}

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	for (auto e : mTimedEvents)
		delete e;
	mTimedEvents.clear();

	for (auto s : mSubscriptions)
	{
		for (auto g : s.second)
			delete g;
		s.second.clear();
	}
	mSubscriptions.clear();
}

void EventManager::BroadcastEvent(Event * pEvent)
{
	for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i)
		gpGameObjectManager->mGameObjects[i]->HandleEvent(pEvent);
}


void EventManager::BroadcastEventToSubscribers(Event * pEvent)
{
	auto &listofSubscribers = mSubscriptions[pEvent->mType];
	for (auto pGO : listofSubscribers)
		pGO->HandleEvent(pEvent);
}
void EventManager::AddTimedEvent(Event * pEvent)
{
	mTimedEvents.push_back(pEvent);
}

void EventManager::Update(float FrameTime)
{
	//Loop through all timed events
	//Decrease timer by FrameTime
	// < 0 ? -> Fire event
	std::list<Event*>::iterator it, itTemp;

	it = mTimedEvents.begin();
	while(it != mTimedEvents.end())
	{
		Event *pEvent = *it;
		pEvent->mTimer -= FrameTime;
		if (pEvent->mTimer < 0.0f)
		{
			//BroadcastEvent(pEvent);
			BroadcastEventToSubscribers(pEvent);

			//delete pEvent;
			it = mTimedEvents.erase(it);
		}
		else
			++it;
	}
}

void EventManager::Subscribe(EventType Type, GameObject * pGameObjectNewSubscriber)
{
	//std::list<GameObject *> &listofSubscribers = mSubscriptions[Type];
	 auto &listofSubscribers = mSubscriptions[Type];

	 for (auto pGO : listofSubscribers)
		 if (pGO == pGameObjectNewSubscriber)
			 return;
	
	 listofSubscribers.push_back(pGameObjectNewSubscriber);
}

void EventManager::Unsubscribe(EventType Type, GameObject * pGameObjectUnsubscriber)
{
	auto &listofSubscribers = mSubscriptions[Type];

	auto it = std::find(listofSubscribers.begin(), listofSubscribers.end(), pGameObjectUnsubscriber);

	if (it == listofSubscribers.end())
		return;
		
	listofSubscribers.erase(it);
}