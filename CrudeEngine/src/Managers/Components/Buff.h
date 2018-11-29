#pragma once

#include "Component.h"

class Buff : public Component
{
public:
	Buff();
	~Buff();

	void Update();
	Component* Create();

public:
	DropType DropType;
	float BuffTime;
	GameObject* Bufficon;
};
