#pragma once

#define SCREEN_WIDTH	960
#define SCREEN_HEIGHT	720

#define PI 3.1415926535897932384626433832795

#define VELOCITY 200.0f
#define BULLET_SPEED 500.0f
#define ENEMY_VELOCITY 50.0f
#define GRENADE_SPEED 200.0f

enum GameObjectTypes
{
	NO_OBJECT = -1,
	PLAYER = 0,
	CRAWLER,
	GHOUL,
	WALL,
	BULLET,
	GRENADE,
	TOMBSTONE,
	HPBAR,
};

enum COMPONENT_TYPE
{
	TRANSFORM,
	SPRITE,
	CONTROLLER,
	BODY,
	ANIMATOR,
	FOLLOW,
	FALLEXPLODE,
	SUBSCRIPTION,
	SPAWNER,
	ATTRIBUTES,
	COMP_NUM
};

enum EventType
{
	WALLCOLLIDE,
	TAKEDAMAGE,
	PLAYERHIT,
	GRENADETHROW,
	GRENADEHIT,
	NUM
};