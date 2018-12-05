/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Frame Rate Controller.h
Purpose:		Header file for Frame Rate Controller
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#ifndef FRC_H
#define FRC_H

#include "SDL_stdinc.h"

class FrameRateController
{
public:
	FrameRateController(Uint32 MaxFrameRate);
	~FrameRateController();

	void FrameStart();
	void FrameEnd();

	float GetFrameTime();

private:
	Uint32 mTickStart;
	Uint32 mTickEnd;
	Uint32 mFrameTime;

	Uint32 mNeededTicksPerFrame;
}; 
#endif // !FRC_H

