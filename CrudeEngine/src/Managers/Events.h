#pragma once

#include "EventManager.h"


class CollideEvent : public Event
{
public:
	CollideEvent() : Event(COLLIDE) { }
	~CollideEvent() { }
};


class PlayerHitEvent : public Event
{
public:
	PlayerHitEvent() : Event(PLAYERHIT) { }
	~PlayerHitEvent() { }
};