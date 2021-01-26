#pragma once

#include<string>
#include<unordered_map>

#include"vendor/glm/glm.hpp"

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int m_Renderer_ID;
	std::string m_File;
	int GetUniformLocation(const std::string &name);
	std::unordered_map<std::string, int> m_locationCache;

	

public:
	Shader(const std::string &filepath);
	~Shader();

	void Bind() const;

	void Unbind() const;

	void Uniform4f(const std::string &name, float v0, float v1, float v2, float v3);

	void Uniform1i(const std::string &name, int value);

	void SetUniformMat4(const std::string &name, const glm::mat4 &matrix);


	unsigned int CompileShader(unsigned int type, const std::string & source);

	int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);

	ShaderSource ParseShader(const std::string & filepath);

	



};