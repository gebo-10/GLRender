#ifndef _METARIAL_HPP
#define _METARIAL_HPP
#pragma once
#include <vector>
#include <ShaderProgram.hpp>
#include <Texture.h>
class Material
{
public:
	vector<Texture *> tex;
	ShaderProgram shader;
public:
	Material();
	~Material();
	bool RegTexture(char * file);
	bool InitShader(GLchar *vShaderFile, GLchar *fShaderFile);
	bool Bind(void);
};
#endif