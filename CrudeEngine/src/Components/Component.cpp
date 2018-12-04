#include "Component.h"
#include "../Managers/GameObject.h"

Component::Component(unsigned int Type)
{
	mpOwner = nullptr;
	mType = Type;
}