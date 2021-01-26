#include "Shader.h"
#include <GL/glew.h>

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

#include"Renderer.h"









Shader::Shader(const std::string &filepath):m_File(filepath),m_Renderer_ID(0)
{
	ShaderSource source = ParseShader(filepath);
	m_Renderer_ID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLLogCall(glDeleteProgram(m_Renderer_ID));
}

void Shader::Bind() const
{
	GLLogCall(glUseProgram(m_Renderer_ID));
}

void Shader::Unbind() const
{
	GLLogCall(glUseProgram(0));
}

/* Here we have used a caching system to make the uniforms faster */

int Shader::GetUniformLocation(const std::string &name)
{
	if (m_locationCache.find(name) != m_locationCache.end())
	{
		return m_locationCache[name];
	}
	GLLogCall(int location=glGetUniformLocation(m_Renderer_ID, name.c_str()));
	if (location == -1)
	{
		std::cout << "Warning Uniform " << name << " doesn't exist" << std::endl;
	}
	m_locationCache[name] = location;
	return location;
}

void Shader::Uniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	GLLogCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::Uniform1i(const std::string & name, int value)
{
	GLLogCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniformMat4(const std::string & name, const glm::mat4 & matrix)
{
	GLLogCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));

}

 unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();  //convert a C++ style string to C style string
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char*)alloca(sizeof(char)*length);
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile Shader !\n" << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << std::endl;
		std::cout << " Message: " << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;



}

int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;


}

ShaderSource Shader::ParseShader(const std::string &filepath)
{
	std::ifstream File(filepath);


	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1

	};
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;


	while (getline(File, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;

			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';

		}
	}
	return { ss[0].str(), ss[1].str() };

}
