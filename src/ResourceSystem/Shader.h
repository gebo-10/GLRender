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
class ShaderParamValue //泛型 类型 得重新设计下   参照下 lua 
{
public:
	bool   b;
	int    i;
	float  f;
	Color color;
	OBJPtr ptr; //话说 用 union 能释放资源吗 ? ?
};
class ShaderParam
{
public:
	ShaderParamType type;
	string param_name;
	string editor_name;//编辑器看到的名字，暂时不用
	ShaderParamValue value;

	ShaderParam() {};
	~ShaderParam() {};
};

class Shader:public ResItem
{
public:
	GLuint id;
	GLuint vertex_shader;//着色器对象
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