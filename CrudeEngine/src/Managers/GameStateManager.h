#pragma once
#include <map>
#include "../Defines.h"
#include "../vendor/simplejson/JSON.h"

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void PrecacheLevels(const char* pFileName);
	void LoadLevel(Levels pLevelName);

private:
	std::map<enum Levels, JSONObject*> mLevels;
};