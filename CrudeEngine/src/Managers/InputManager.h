/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		InputManager.h
Purpose:		Header file for Input Manager
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_Milestone1
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	10/18/2018

- End Header --------------------------------------------------------*/

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "SDL_stdinc.h"

class Input_Manager
{
public:
	Input_Manager();
	~Input_Manager();

	void Update();

	bool IsPressed(unsigned int KeyScanCode); //From SDL_Scancode
	bool IsTriggered(unsigned int KeyScanCode);
	bool IsReleased(unsigned int KeyScanCode);

	bool IsMouseClicked(unsigned int KeyScanCode);

private:
	Uint8 mCurrentState[512];
	Uint8 mPreviousState[512];
};


#endif // !INPUT_MANAGER_H

