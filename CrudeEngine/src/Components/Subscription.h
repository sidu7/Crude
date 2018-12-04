#pragma once

#include "Component.h"
#include <vector>

class Subscription : public Component
{
public:
	Subscription();
	~Subscription();

	void Update();
	void Serialize(JSONObject obj);
	Component* Create();

public:
	std::vector<unsigned int> mEventSubscriptions;

};