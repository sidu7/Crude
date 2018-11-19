#pragma once

#include <vector>
#include "../Maths/Vector2D.h"


class Component;

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
		void ScaleToBody();
		void ResetScale();

public:
		GameObjectTypes mType;
		float mDeathDelay;
		std::vector<Component*> mComponents;
		bool Destroyed;

private:
	Vector2D mTempScale;
};
