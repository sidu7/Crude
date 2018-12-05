/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		EventManager.h
Purpose:		Header file for Event Manager
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once
#include <list>
#include <unordered_map>

#include "../Defines.h"

class GameObject;



class Event
{
public:
	Event(EventType Type);
	virtual ~Event() {}

public:
	EventType mType;
	float mTimer;
};

class EventManager
{
public:
	EventManager();
	~EventManager();

	void BroadcastEvent(Event *pEvent);
	void BroadcastEventToSubscribers(Event * pEvent);
	void AddTimedEvent(Event *pEvent);
	void Update(float FrameTime);
	void Subscribe(EventType Type, GameObject *pGameObject);

	void Unsubscribe(EventType Type, GameObject * pGameObjectUnsubscriber);

public:
	std::list<Event*> mTimedEvents;
	std::unordered_map<EventType, std::list<GameObject*>> mSubscriptions;
};