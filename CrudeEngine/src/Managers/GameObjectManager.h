/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		GameObjectManager.h
Purpose:		Header file for GameObject Manager
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include <vector>
#include <map>

class GameObject;
class Component;

class GameObjectManager
{
	public:
	GameObjectManager();
	~GameObjectManager();
	void Destroy(GameObject* pGameObject);
	void Update();

public:
	std::vector<GameObject *> mGameObjects;
	std::vector<GameObject*> mStaticDeadObjects;
	std::map<unsigned int, Component*> mComponentMap;

private:
	std::vector<GameObject*> mDeleteObjects;
};