#include "Sprite.h"
#include <string>
#include "../Managers/ResourceManager.h"

extern ResourceManager *gpResourceManager;
extern Shader *gpShader;

Sprite::Sprite() : Component(SPRITE), mpTexture(nullptr)
{

}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	mpTexture->Bind();
	gpShader->Bind();
	gpShader->SetUniform1i("TextureS", 0);
}

void Sprite::Serialize(JSONObject obj)
{
	std::string fullPath = "res/textures/";
	std::wstring ws = obj[L"File"]->AsString();
	std::string imagename(ws.begin(), ws.end());
	fullPath += imagename;

	mpTexture = gpResourceManager->LoadSurface(fullPath.c_str());
}

Component * Sprite::Create()
{
	return new Sprite();
}
