#pragma once

#include <string>

class Matrix3D;

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
	int GetUniformLocation(const std::string& name);
};