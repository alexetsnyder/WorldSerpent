#pragma once
#include <string>
#include <glm/glm.hpp>

using namespace std;

class Shader
{
	public:
		Shader();
		Shader(string vShaderFile, string fShaderFile);

		void setVShader(string vShaderFile);
		void setFShader(string fShaderFile);

		bool compile(char errorMsg[512]);
		bool link(char errorMsg[512]);
		void use();

		void setUniformMatrix4fv(string name, glm::mat4 uniformMat);

		void free();

	private:
		string loadFile(string fileName);
		bool compile(unsigned int shader, char errorMsg[512]);

		unsigned int vShader;
		unsigned int fShader;
		unsigned int program;
};

