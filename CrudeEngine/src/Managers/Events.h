#pragma once

#include "EventManager.h"
#include "Components/Body.h"


class WallCollideEvent : public Event
{
public:
	WallCollideEvent() : Event(WALLCOLLIDE) { }
	~WallCollideEvent() { }
};


class PlayerHitEvent : public Event
{
public:
	PlayerHitEvent() : Event(PLAYERHIT) { }
	~PlayerHitEvent() { }
};

class BulletHitEvent : public Event
{
public:
	BulletHitEvent() : Event(BULLETHIT) { }
	~BulletHitEvent() { }
};

class ThrowGrenadeEvent : public Event
{
public:
	ThrowGrenadeEvent() : Event(GRENADETHROW) { }
	~ThrowGrenadeEvent() { }
	Body* pBody;
};