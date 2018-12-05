/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Spawner.h
Purpose:		Header file for Spawner Component
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"

class Event;

class Spawner : public Component
{
public:
	Spawner();
	~Spawner();

	void Update();
	Component* Create();
	void HandleEvent(Event *pEvent);
	
public:
	float mCurrDelay;
	float mStartDelay;
	static float mStatic;
};