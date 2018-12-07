/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		GameObject.h
Purpose:		Header file for GameObject template
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once

#include <vector>
#include "../Maths/Vector2D.h"
#include "../Components/Component.h"

class Sprite;
class Transform;
class Controller;
class Event;
enum GameObjectTypes;

class GameObject{
public: 
		GameObject(GameObjectTypes type);
		~GameObject();
	
		bool Update();
		Component* AddComponent(unsigned int Type);
		Component *GetComponent(unsigned int Type);
		void RemoveComponent(unsigned int Type);
		void SetTransform(float posX, float posY, float scaleX, float scaleY, float angle);
		void SetSprite(const char* filePath);
		void HandleEvent(Event* pEvent);

		
public:
		GameObjectTypes mType;
		float mDeathDelay;
		std::vector<Component*> mComponents;
		bool Destroyed;

private:
	Vector2D mTempScale;
};
