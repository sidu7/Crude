#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Component.h"
#include <array>

class GameObject;
class Event;

class Controller : public Component
{
public:
	Controller();
	~Controller();
	
	void Update();
	Component* Create();
	void HandleEvent(Event* pEvent);

private:
	bool moving;
	std::array<bool,4> wallcollision;
};

#endif