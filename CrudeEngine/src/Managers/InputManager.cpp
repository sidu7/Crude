/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		InputManager.cpp
Purpose:		Input Handling for the Game Engine
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "InputManager.h"
#include "SDL_keyboard.h"
#include "SDL.h"
#include <string>
#include <iostream>


Input_Manager::Input_Manager()
{
	SDL_memset(mCurrentState, 0, 512 * sizeof(Uint8));
	SDL_memset(mPreviousState, 0, 512 * sizeof(Uint8));
	SDL_memset(mPrevMouseState, 0, 3 * sizeof(Uint8));
	SDL_memset(mCurrentMouseState, 0, 3 * sizeof(Uint8));
}

Input_Manager::~Input_Manager()
{
}

void Input_Manager::Update()
{
	//fetch mouse state

	SDL_memcpy(mPrevMouseState, mCurrentMouseState, 3 * sizeof(Uint8));

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			mCurrentMouseState[e.button.button - 1] = true;
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			mCurrentMouseState[e.button.button - 1] = false;
		}
	}

	//fetch keyboard state
	int numberOfFetchedKeys = 0;
	const Uint8* pCurrentKeyStates = SDL_GetKeyboardState(&numberOfFetchedKeys);

	if (numberOfFetchedKeys > 512)
	{
		numberOfFetchedKeys = 512;
	}

	SDL_memcpy(mPreviousState, mCurrentState, 512 * sizeof(Uint8));
	SDL_memcpy(mCurrentState, pCurrentKeyStates, numberOfFetchedKeys * sizeof(Uint8));
}

bool Input_Manager::IsPressed(unsigned int KeyScanCode)
{
	if (KeyScanCode >= 512)
		return false;

	if (mCurrentState[KeyScanCode])
		return true;

	return false;
}

bool Input_Manager::IsTriggered(unsigned int KeyScanCode)
{
	if (KeyScanCode >= 512)
		return false;

	if (mCurrentState[KeyScanCode] && !mPreviousState[KeyScanCode])
		return true;

	return false;
}

bool Input_Manager::IsReleased(unsigned int KeyScanCode)
{
	if (KeyScanCode >= 512)
		return false;

	if (!mCurrentState[KeyScanCode] && mPreviousState[KeyScanCode])
		return true;

	return false;
}

bool Input_Manager::IsMouseClicked(unsigned int KeyScanCode)
{
	if (mCurrentMouseState[KeyScanCode - 1] && !mPrevMouseState[KeyScanCode - 1])
		return true;
	return false;
}
