/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Frame Rate Controller.cpp
Purpose:		Frame Rate Controller for the Game Engine
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_Milestone1
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	10/18/2018

- End Header --------------------------------------------------------*/


#include "Frame Rate Controller.h"
#include "SDL_timer.h"

FrameRateController::FrameRateController(Uint32 MaxFrameRate)
{
	mTickStart = mTickEnd = mFrameTime = 0;

	if (MaxFrameRate != 0)
	{
		mNeededTicksPerFrame = 1000 / MaxFrameRate;
	}
	else
	{
		mNeededTicksPerFrame = 0;
	}
}

FrameRateController::~FrameRateController()
{

}

void FrameRateController::FrameStart()
{
	mTickStart = SDL_GetTicks();
}

void FrameRateController::FrameEnd()
{
	mTickEnd = SDL_GetTicks();
	while (mTickEnd - mTickStart < mNeededTicksPerFrame)
	{
		mTickEnd = SDL_GetTicks();
	}
	mFrameTime = mTickEnd - mTickStart;
}

float FrameRateController::GetFrameTime()
{
	return (float)mFrameTime / 1000.0f;
}
