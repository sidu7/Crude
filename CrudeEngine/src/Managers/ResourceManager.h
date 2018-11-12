/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		ResourceManager.h
Purpose:		Header file for Resource Manager
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_Milestone1
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	10/18/2018

- End Header --------------------------------------------------------*/

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <unordered_map>
#include "../OpenGL/Texture.h"


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Texture *LoadSurface(const char *pFilePath);

private:
	std::unordered_map<std::string, Texture*> mTextures;
};

#endif // !RESOURCE_MANAGER_H
