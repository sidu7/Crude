#include <vector>

class Component;

class Sprite;
class Transform;
class Controller;
class Event;

class GameObject{
	public: 
		GameObject(int type);
		~GameObject();
	
		void Update();
		Component* AddComponent(unsigned int Type);
		Component *GetComponent(unsigned int Type);
		void RemoveComponent(unsigned int Type);
		void SetTransform(float posX, float posY, float scaleX, float scaleY, float angle);
		void SetSprite(const char* filePath);
		void HandleEvent(Event* pEvent);

	public:
		int mType;
		float mDeathDelay;
		std::vector<Component*> mComponents;
};
