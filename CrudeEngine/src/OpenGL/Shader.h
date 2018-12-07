/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Shader.h
Purpose:		OpenGL Shaders Compilation and Linking
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once

#include <string>

struct Matrix3D;

struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_VertexFilePath, m_FragmentFilePath;
public:
	Shader(std::string vertexFilePath, std::string fragmentFilePath);
	~Shader();

	unsigned int CreateProgram(std::string& vertexSource, std::string& fragmentSource);
	unsigned int CompileShader(unsigned int type, std::string& Source);
	ShaderSource ParseShader(std::string vertexFilePath, std::string fragmentFilePath);

	void Bind() const;
	void Unbind() const;
	void SetUniform1i(const std::string& name, int i);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniformMat4f(const std::string& name, Matrix3D* matrix);
	void SetUniformMat4fLoc(int location, Matrix3D* matrix);
	int GetUniformLocation(const std::string& name);
};