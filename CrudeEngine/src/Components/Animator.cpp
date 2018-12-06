/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Animator.cpp
Purpose:		Sprite Animation Component of GameObject
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "Animator.h"
#include "../../vendor/dirent/dirent.h"
#include <iostream>
#include "../Managers/ResourceManager.h"
#include "../Managers/Frame Rate Controller.h"
#include "../Managers/GameObject.h"
#include "../Managers/GameObjectManager.h"
#include "Sprite.h"
#include "Transform.h"

extern ResourceManager *gpResourceManager;
extern GameObjectManager *gpGameObjectManager;
extern FrameRateController *gpFrameRateController;
extern int Tombstones;

Animator::Animator() : Component(ANIMATOR), mCurrState(""), mCurrFrame(0), mCurrDelay(0.0f), 
PlayingAnimation(false), DestroyAfterAnimation(false)
{
}

Animator::~Animator()
{
	for (auto a : mAnimations)
	{
		a.second.clear();
	}
	mAnimations.clear();
}

void Animator::LoadSpriteSheet(std::string FilePath,std::string type)
{
	DIR *pDir;
	struct dirent *entry;
	std::vector<Texture*> sheet;

	if (pDir = opendir(FilePath.c_str())) {
		while (entry = readdir(pDir)) {
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
			{
				std::string path = FilePath + "/" + entry->d_name;
				Texture* TempTex = gpResourceManager->LoadSurface(path.c_str());
				sheet.push_back(TempTex);
			}
		}
		closedir(pDir);
	}
	mAnimations[type] = sheet;
}

void Animator::Update()
{
	Sprite *pSp = static_cast<Sprite*>(mpOwner->GetComponent(SPRITE));

	if (PlayingAnimation)
	{
		
		if (mCurrDelay >= 0.0f)
			mCurrDelay += gpFrameRateController->GetFrameTime();
		if (mCurrDelay < 0.0f || mCurrDelay > (1.0f / mAnimations[mCurrState].size()))
		{
			if (mCurrFrame < (int)mAnimations[mCurrState].size())
				pSp->mpTexture = mAnimations[mCurrState][mCurrFrame++];
			if (mCurrFrame >= (int)mAnimations[mCurrState].size())
			{
				PlayingAnimation = false;
				mCurrFrame = 0;
				if (DestroyAfterAnimation)
					gpGameObjectManager->Destroy(mpOwner);
				if (mCurrState == "die" || mCurrState == "destroy")
				{
					if (mCurrState == "die")
					{
						mpOwner->RemoveComponent(FOLLOW);
						mpOwner->RemoveComponent(SUBSCRIPTION);
						mpOwner->mDeathDelay = 1.0f;
					}
					else
					{
						Tombstones--;
					}
					mpOwner->RemoveComponent(ANIMATOR);
					mpOwner->RemoveComponent(ATTRIBUTES);
					gpGameObjectManager->MoveToStaticDead(mpOwner);
				}
				else
					ResetState();
			}
			mCurrDelay = 0.0f;
		}
	}
	else
	{
		mCurrDelay += gpFrameRateController->GetFrameTime();
		if (mCurrDelay >(1.0f / mAnimations[mCurrState].size()))
		{
			if (mCurrFrame < (int)mAnimations[mCurrState].size())
				pSp->mpTexture = mAnimations[mCurrState][mCurrFrame++];
			if (mCurrFrame >= (int)mAnimations[mCurrState].size())
				mCurrFrame = 0;
			mCurrDelay = 0.0f;
		}
	}
}

void Animator::Serialize(JSONObject obj)
{
	JSONArray Spritesheets = obj[L"Sprites"]->AsArray();

	for (int i = 0; i < (int)Spritesheets.size(); ++i) {
		JSONObject eobj = Spritesheets[i]->AsObject();
		std::wstring wp = eobj[L"FileDir"]->AsString();
		std::wstring wt = eobj[L"Type"]->AsString();
		LoadSpriteSheet(std::string(wp.begin(), wp.end()), std::string(wt.begin(), wt.end()));
		if (eobj.find(L"Default") != eobj.end())
			mCurrState = std::string(wt.begin(), wt.end());
	}
}

void Animator::SetState(std::string state)
{
	mCurrState =  state;
}

void Animator::ResetState()
{
	mCurrState = "idle";
	Sprite *pSp = static_cast<Sprite*>(mpOwner->GetComponent(SPRITE));
	if (mAnimations[mCurrState].size() != 0)
		pSp->mpTexture = mAnimations[mCurrState][0];
}

void Animator::PlayAnimation(std::string animation,bool destroy)
{
	mCurrState = animation;
	PlayingAnimation = true;
	mCurrDelay = -1.0f;
	mCurrFrame = 0;
	DestroyAfterAnimation = destroy;
}

Component * Animator::Create()
{
	return new Animator();
}
