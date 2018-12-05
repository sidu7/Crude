/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Texture.h
Purpose:		Loading Textures from file for OpenGL
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once
#include "Renderer.h"
#include <string>

class Texture
{
private:
	unsigned int mRendererID;
	int mWidth, mHeight, mBPP;
	unsigned char* mLocalBuffer;

public:
	std::string mFilePath;
	Texture(const std::string& FilePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
};