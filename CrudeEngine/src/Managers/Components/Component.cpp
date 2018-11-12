#include "Component.h"
#include "../GameObject.h"

Component::Component(unsigned int Type)
{
	mpOwner = nullptr;
	mType = Type;
}