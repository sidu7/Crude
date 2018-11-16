#pragma once
#include "Component.h"

class Transform;
class Body;
class Vector2D;

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
	float getAngleVector(Vector2D mVec1, Vector2D aVec2);
};
