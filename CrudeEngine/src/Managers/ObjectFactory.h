/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		ObjectFactory.h
Purpose:		Header file for Object Factory
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once
#include <map>
#include "../vendor/simplejson/JSON.h"

class GameObject;
enum GameObjectTypes;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	void LoadArchetypes(const char *pFileName);
	void LoadLevel(const char *pFileName);
	GameObject* LoadObject(const char* pFileName, GameObjectTypes type);
	GameObject* LoadObject(JSONObject obj, GameObjectTypes type);
	GameObject* GetArcheType(GameObjectTypes type);

private:
	std::map<GameObjectTypes,JSONObject*> mArchetypes;
};
