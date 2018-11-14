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
	
	public:
	std::vector<GameObject *> mGameObjects;
	std::map<unsigned int, Component*> mComponentMap;
};