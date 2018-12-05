/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Component.h
Purpose:		Header file for Component
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#ifndef COMPONENT_H
#define COMPONENT_H

#include "stdio.h"
#include "../../vendor/simplejson/JSON.h"
#include "../../Defines.h"

class GameObject;
class Event;

class Component
{
	public:
	Component(unsigned int Type);
	virtual ~Component() { }

	virtual void Update() = 0;
	unsigned int GetType() { return mType; }

	virtual void Serialize(JSONObject obj) {}

	virtual Component* Create() = 0;
	virtual void HandleEvent(Event* pEvent) {}

	public:
	
	GameObject *mpOwner;
	
	private:
	
	unsigned int mType;

};

#endif