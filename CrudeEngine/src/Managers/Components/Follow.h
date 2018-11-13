#pragma once
#include "Component.h"

class Transform;
class Body;

class Follow : public Component
{
public:
	Follow();
	~Follow();

	void Initialize();

	void Update();
	Component* Create();

private:
	Transform *mPlayerPos;
	Body *mBody;
	bool Init;
};
