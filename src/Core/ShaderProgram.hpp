#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#pragma once
#include <Base.hpp>
#include<GL/glew.h>

class ShaderProgram
{
public:
	GLuint id;
	ShaderProgram();
	~ShaderProgram();
	char * readTextFile(char * file_name);
	GLuint buildShader(GLchar *vShaderFile, GLchar *fShaderFile);
};


#endif