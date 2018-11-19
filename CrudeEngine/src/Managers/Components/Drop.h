#pragma once

#include "Component.h"

class Drop : public Component
{
public:
	Drop();
	~Drop();

	void Update();
	Component* Create();

public:
	DropType mType;

private:
	bool Dropped;
};