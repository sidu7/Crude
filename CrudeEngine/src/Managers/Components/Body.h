#pragma once

#include "../CollisionManager.h"
#include "../../Maths/Vector2D.h"
#include "Component.h"

class Body : public Component {
public:
	Body();
	~Body();

	void Update();
	void Serialize(JSONObject obj);
	void Initialize();
	void Integrate(float Gravity, float DeltaTime);
	void AddVelocity(float velocity);
	Component* Create();


public:
	Vector2D mPosition;
	Vector2D mPrevPosition;
	Vector2D mVelocity;
	Vector2D mAcceleration;
	Vector2D mTotalForce;
	float mMass, mInvMass;
	float mAngV;

	Shape *mpShape;
};