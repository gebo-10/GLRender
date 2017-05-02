#ifndef _METARIAL_HPP
#define _METARIAL_HPP
#pragma once
#include <vector>
#include <Shader.h>
#include <Texture.h>
#include <ResourceManager.h>
class Material :public ResItem
{
public:
	ShaderPtr shader;
	std::vector< ShaderParam > param;
public:
	Material();
	~Material();
	bool Init();
	bool ParseParam(char * jsonstr);
	bool Bind(void);
};
typedef shared_ptr<Material> MaterialPtr;
#endif