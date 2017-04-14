#ifndef _METARIAL_HPP
#define _METARIAL_HPP
#pragma once
#include <vector>
#include <Shader.h>
#include <Texture.h>
class Material
{
public:
	vector<Texture *> tex;
	shared_ptr<Shader> shader;
public:
	Material();
	~Material();
	bool RegTexture(char * file);
	bool InitShader(string filename);
	bool Bind(void);
};
#endif