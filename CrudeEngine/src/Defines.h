/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Defines.h
Purpose:		All required Defines and Enums
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once

#define SCREEN_WIDTH	960
#define SCREEN_HEIGHT	720

#define PI 3.1415926535897932384626433832795f

#define VELOCITY 200.0f
#define BULLET_SPEED 500.0f
#define GHOUL_VELOCITY 50.0f
#define CRAWLER_VELOCITY 100.0f
#define GRENADE_SPEED 150.0f

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
	DROPITEM,
	TOMB1HP,
	TOMB2HP,
	STARTBUTTON,
	HOWTOPLAYBUTTON,
	QUITBUTTON,
	BACKBUTTON,
	OBJ_NUM
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
	DROP,
	BUFF,
	COMP_NUM
};

enum EventType
{
	WALLCOLLIDE,
	TAKEDAMAGE,
	PLAYERHP,
	GRENADETHROW,
	GRENADEHIT,
	DROPPICKED,
	TOMBHIT,
	TOMBDESTROY,
	BUTTONCLICK,
	NUM
};

enum DropType
{
	MEDKIT = 1,
	DGRENADE = 3,
	DOUBLEDMG = 5,
	CRAWL = 7
};