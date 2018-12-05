/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Events.h
Purpose:		List of all Events
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once

#include "EventManager.h"
#include "../Components/Body.h"


class WallCollideEvent : public Event
{
public:
	WallCollideEvent() : Event(WALLCOLLIDE) { side = { 0 }; }
	~WallCollideEvent() { }
	unsigned int side; // 0:left, 1:top, 2:right, 3:bottom
};


class PlayerHPEvent : public Event
{
public:
	PlayerHPEvent() : Event(PLAYERHP) { }
	~PlayerHPEvent() { }
	float HPChange;
};

class TakeDamage : public Event
{
public:
	TakeDamage() : Event(TAKEDAMAGE) { }
	~TakeDamage() { }
	int DamageDealt;
};

class ThrowGrenadeEvent : public Event
{
public:
	ThrowGrenadeEvent() : Event(GRENADETHROW) { }
	~ThrowGrenadeEvent() { }
	Body* pBody;
};

class GrenadeHit : public Event
{
public:
	GrenadeHit() : Event(GRENADEHIT) { }
	~GrenadeHit() { }
};

class DropPicked : public Event
{
public:
	DropPicked() : Event(DROPPICKED) { }
	~DropPicked() { }
	DropType Drop;
};

class TombHitEvent : public Event 
{
public:
	TombHitEvent() : Event(TOMBHIT) { }
	~TombHitEvent() { }
	int tomb;
	float HPLost;
};

class TombDestroyed : public Event
{
public: 
	TombDestroyed() : Event(TOMBDESTROY) { }
	~TombDestroyed() { }
	int tomb;
};