/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		ResouceManager.cpp
Purpose:		Resource handling for Game Engine
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (auto &element : mTextures)
	{
		element.second->~Texture(); // first is key and second is actual surface that needs to be freed
	}
	mTextures.clear();
}


Texture *ResourceManager::LoadSurface(const char *pFilePath)
{
	//Check hash map
	Texture *pTexture = mTextures[pFilePath];

	//Already loaded?
	if (pTexture)
		return pTexture;

	//Load it
	pTexture =  new Texture(pFilePath);

	//Load successful? Add to hash map
	if (pTexture)
	{
		mTextures[pFilePath] = pTexture;
	}

	//return to user
	return pTexture;
}