/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Animator.h
Purpose:		Header file for Animator Component
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"
#include <map>

class Texture;

class Animator : public Component
{
public :
	Animator();
	~Animator();

	void LoadSpriteSheet(std::string FilePath, std::string type);
	void Update();
	void Serialize(JSONObject obj);
	void SetState(std::string state);
	void ResetState();
	void PlayAnimation(std::string animation, bool destroy);
	Component* Create();


public :
	std::map<std::string , std::vector<Texture *>> mAnimations;
	std::string mCurrState;
	bool PlayingAnimation;
private:
	int mCurrFrame;
	float mCurrDelay;
	bool DestroyAfterAnimation;
};
