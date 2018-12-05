/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Controller.h
Purpose:		Header file for Controller Component
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Component.h"
#include <array>

class GameObject;
class Event;
struct Vector2D;

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
	float getAngleVector(Vector2D mVec1, Vector2D aVec2);
	float getAngleFromMouse(Vector2D PlayerPos);
};

#endif