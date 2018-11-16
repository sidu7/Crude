#pragma once

#include "Component.h"

class Event;

class Spawner : public Component
{
public:
	Spawner();
	~Spawner();

	void Update();
	Component* Create();
	void HandleEvent(Event *pEvent);
	
public:
	float mCurrDelay;
	float mStartDelay;
	static float mStatic;
};