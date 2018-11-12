#ifndef COMPONENT_H
#define COMPONENT_H

#include "stdio.h"
#include "../../vendor/simplejson/JSON.h"
#include "../../Defines.h"

class GameObject;
class Event;

class Component
{
	public:
	Component(unsigned int Type);
	virtual ~Component() { }

	virtual void Update() = 0;
	unsigned int GetType() { return mType; }

	virtual void Serialize(JSONObject obj) {}

	virtual Component* Create() = 0;
	virtual void HandleEvent(Event* pEvent) {}

	public:
	
	GameObject *mpOwner;
	
	private:
	
	unsigned int mType;

};

#endif