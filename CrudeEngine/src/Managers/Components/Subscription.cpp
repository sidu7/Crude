#include "Subscription.h"
#include "../Events.h"

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
