/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Sprite.cpp
Purpose:		Sprite texture Component of GameObject
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "Sprite.h"
#include <string>
#include "../Managers/ResourceManager.h"

extern ResourceManager *gpResourceManager;
extern Shader *gpShader;

Sprite::Sprite() : Component(SPRITE), mpTexture(nullptr)
{

}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	mpTexture->Bind();
	gpShader->Bind();
	gpShader->SetUniform1i("TextureS", 0);
}

void Sprite::Serialize(JSONObject obj)
{
	std::string fullPath = "res/textures/";
	std::wstring ws = obj[L"File"]->AsString();
	std::string imagename(ws.begin(), ws.end());
	fullPath += imagename;

	mpTexture = gpResourceManager->LoadSurface(fullPath.c_str());
}

Component * Sprite::Create()
{
	return new Sprite();
}
