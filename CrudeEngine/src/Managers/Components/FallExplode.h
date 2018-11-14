#pragma once

#include "Component.h"

class FallExplode : public Component
{
public:
	FallExplode();
	~FallExplode();

	void Update();
	void Serialize(JSONObject obj);
	Component* Create();
	void HandleEvent(Event *pEvent);
	
private:
	float mCurrDelay;
	float mDelayLimit;
	bool Exploding;
};

