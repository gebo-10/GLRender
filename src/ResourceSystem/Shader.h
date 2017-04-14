#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#pragma once
#include <Base.hpp>
#include<GL/glew.h>
#include <ResourceManager.h>
class Shader:public ResItem
{
public:
	GLuint id;
	GLuint vertex_shader;//着色器对象
	GLuint frag_shader;

	Shader();
	~Shader();
	
	bool Init();
	void BuildShader(GLchar * vertex_file, GLchar * frag_file);
	bool BuildVertexShader(char * source);
	bool BuildFragShader(char * source);
	bool BuildProgram();

};

#endif