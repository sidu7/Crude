/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Sprite.h
Purpose:		Header file for Sprite Component
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#ifndef SPRITE_H
#define SPRITE_H


#include "Component.h"
#include "../../OpenGL/Texture.h"
#include "../../OpenGL/Shader.h"

class Sprite : public Component
{
public:
	Sprite();
	~Sprite();

	void Update();

	void Serialize(JSONObject obj);
	Component* Create();

public:
	Texture *mpTexture;
};

#endif // !SPRITE_H

