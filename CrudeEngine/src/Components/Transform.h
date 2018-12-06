/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Transform.h
Purpose:		Header file for Transform Component
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "Component.h"
#include "../../Maths/Matrix2D.h"
#include "../../OpenGL/Shader.h"
#include "../../Maths/Vector2D.h"

class Event;

class Transform : public Component
{
	public:
	Transform();
	~Transform();

	void Update();
	
	void UpdateLine();
	void UpdateDebug();
	void Serialize(JSONObject obj);
	void HandleEvent(Event *pEvent);

	Component* Create();
	
public:
	Vector2D mPosition;
	Vector2D mScale;
	float mAngle;
	bool Debug;

private:
	Matrix3D trans;
	Matrix3D mvp;

};