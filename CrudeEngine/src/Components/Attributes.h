/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Attributes.h
Purpose:		Header file for Attributes Component
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/
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

public:
	int mCurrHP;
	int mTotalHP;
	int mDamage;
};