#version 330 core

layout(location = 0) out vec4 color;

in vec2 u_TexCoord;

uniform sampler2D TextureS;
uniform int debug;

void main()
{
	if (debug == 0)
		color = texture(TextureS, u_TexCoord);
	else
		color = vec4(0.0, 1.0, 0.0, 1.0);
}