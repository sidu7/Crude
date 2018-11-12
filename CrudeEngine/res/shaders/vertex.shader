#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 TexCoord;

out vec2 u_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position ;
	u_TexCoord = TexCoord;
}