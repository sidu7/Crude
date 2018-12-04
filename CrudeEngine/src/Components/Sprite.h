#ifndef SPRITE_H
#define SPRITE_H


#include "Component.h"
#include "../../OpenGL/Texture.h"
#include "../../OpenGL/Shader.h"

class Sprite : public Component
{
public:
	Sprite();
	~Sprite();

	void Update();

	void Serialize(JSONObject obj);
	Component* Create();

public:
	Texture *mpTexture;
};

#endif // !SPRITE_H

