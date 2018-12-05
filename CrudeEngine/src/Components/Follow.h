/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Follow.h
Purpose:		Header file for Follow Component
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once
#include "Component.h"

class Transform;
class Body;
struct Vector2D;

class Follow : public Component
{
public:
	Follow();
	~Follow();

	void Initialize();

	void Update();
	Component* Create();

private:
	Transform *mPlayerPos;
	Body *mBody;
	bool Init;
	float getAngleVector(Vector2D mVec1, Vector2D aVec2);
};
