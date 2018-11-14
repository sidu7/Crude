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
