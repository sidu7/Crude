#pragma once

#include "EventManager.h"
#include "Components/Body.h"


class WallCollideEvent : public Event
{
public:
	WallCollideEvent() : Event(WALLCOLLIDE) { side = { 0 }; }
	~WallCollideEvent() { }
	unsigned int side; // 0:left, 1:top, 2:right, 3:bottom
};


class PlayerHitEvent : public Event
{
public:
	PlayerHitEvent() : Event(PLAYERHIT) { }
	~PlayerHitEvent() { }
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