#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#pragma once
#include <Base.hpp>
#include<GL/glew.h>
#include <ResItem.h>

enum ShaderParamType
{
	SPT_BOOL,
	SPT_INT,
	SPT_FLOAT,
	SPT_COLOR,
	SPT_TEXTURE,
};
class ShaderParamValue //���� ���� �����������   ������ lua 
{
public:
	bool   b;
	int    i;
	float  f;
	Color color;
	OBJPtr ptr; //��˵ �� union ���ͷ���Դ�� ? ?
};
class ShaderParam
{
public:
	ShaderParamType type;
	string param_name;
	string editor_name;//�༭�����������֣���ʱ����
	ShaderParamValue value;

	ShaderParam() {};
	~ShaderParam() {};
};

class Shader:public ResItem
{
public:
	GLuint id;
	GLuint vertex_shader;//��ɫ������
	GLuint frag_shader;

	std::vector< ShaderParam > param;

	Shader();
	~Shader();
	
	bool LoadCallback();
	bool ParseParam(char * jsonstr);
	void BuildShader(GLchar * vertex_file, GLchar * frag_file);
	bool BuildVertexShader(char * source);
	bool BuildFragShader(char * source);
	bool BuildProgram();

};
typedef shared_ptr<Shader> ShaderPtr;
#endif