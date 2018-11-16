#pragma once

#include "Component.h"

class Event;

class Attributes : public Component
{
public:
	Attributes();
	~Attributes();

	void Update();
	void Serialize(JSONObject obj);
	Component* Create();
	void HandleEvent(Event *pEvent);
	inline int GetCurrentHP() { return mCurrHP; }

private:
	int mCurrHP;
	int mTotalHP;
	int mDamage;
};