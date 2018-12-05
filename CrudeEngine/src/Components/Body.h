/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Body.h
Purpose:		Header file for Body Component
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once

#include "../Managers/CollisionManager.h"
#include "../Maths/Vector2D.h"
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
	void HandleEvent(Event* pEvent);
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