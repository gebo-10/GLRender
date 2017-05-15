#ifndef _METARIAL_H
#define _METARIAL_H
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
	bool LoadCallback();
	bool ParseParam(char * jsonstr);
	bool Bind(void);
};
typedef shared_ptr<Material> MaterialPtr;
#endif