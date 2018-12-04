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
