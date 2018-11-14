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