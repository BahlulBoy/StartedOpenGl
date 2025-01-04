#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragPath)
	{
		std::string vertexCode;
		std::string fragCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragPath);
			std::stringstream vStreamShader, fStreamShader;

			vStreamShader << vShaderFile.rdbuf();
			fStreamShader << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vStreamShader.str();
			fragCode = fStreamShader.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "EKTRAKSI FILE SHADER TIDAK BERHASIL" << std::endl;
		}
		const char* vertexShaderSource = vertexCode.c_str();
		const char* fragShaderSource = fragCode.c_str();

		int success;
		char infoLog[512];

		unsigned int vertexShader;
		// mengenerate shader baru
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		// menaruh source shader ke vertexshader
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		// compile shader
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "vertext shader failed : " << infoLog << std::endl;
		}


		// untuk frag
		unsigned int fragShader;
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragShaderSource, NULL);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
			std::cout << "fragment shader failed : " << infoLog << std::endl;
		}

		// mengenerate shader program
		ID = glCreateProgram();
		// link 2 shader kedalam program shader
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragShader);
		glLinkProgram(ID);

		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(fragShader, 512, NULL, infoLog);
			std::cout << "shader program failed : " << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
	}

	void use() {
		glUseProgram(ID);
	}

	void deleteProgram() {
		glDeleteProgram(ID);
	}
};

#endif