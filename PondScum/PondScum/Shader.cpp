#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader()
{

}

Shader::Shader(string vShaderFile, string fShaderFile)
{	
	setVShader(vShaderFile);
	setFShader(fShaderFile);
}

void Shader::setVShader(string vShaderFile)
{
	vShader = glCreateShader(GL_VERTEX_SHADER);
	string vShaderStr = loadFile(vShaderFile);
	const char* vShaderSource = vShaderStr.c_str();
	glShaderSource(vShader, 1, &vShaderSource, NULL);

}

void Shader::setFShader(string fShaderFile)
{
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	string fShaderStr = loadFile(fShaderFile);
	const char* fShaderSource = fShaderStr.c_str();
	glShaderSource(fShader, 1, &fShaderSource, NULL);
}

bool Shader::compile(char errorMsg[512])
{
	if (!compile(vShader, errorMsg) ||
		!compile(fShader, errorMsg))
	{
		return false;
	}
	return true;
}

bool Shader::compile(unsigned int shader, char errorMsg[512])
{
	int success;
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, errorMsg);
		return false;
	}
	return true;
}

bool Shader::link(char errorMsg[512])
{
	int success;

	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, errorMsg);
		return false;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return true;
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::free()
{
	glDeleteProgram(program);
}

string Shader::loadFile(string fileName)
{
	string file = "";
	string line = "";

	ifstream inFile(fileName);
	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			file += line + "\n";
		}
		inFile.close();

		return file;
	}

	return "";
}

void Shader::setUniformMatrix4fv(string name, glm::mat4 uniformMat)
{
	int matLoc = glGetUniformLocation(program, name.c_str());
	glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(uniformMat));
}