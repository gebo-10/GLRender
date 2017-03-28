#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM
#pragma once
#include <Base.hpp>
#include<GL/glew.h>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	char * readTextFile(char * file_name);
	GLuint buildShader(GLchar *vShaderFile, GLchar *fShaderFile);
	GLuint id;
private:
	
};


#endif