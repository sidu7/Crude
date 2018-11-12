#version 330 core

layout(location = 0) out vec4 color;

in vec2 u_TexCoord;

uniform sampler2D TextureS;

void main()
{
	vec4 texcolor = texture(TextureS, u_TexCoord);
	color = texcolor;
}