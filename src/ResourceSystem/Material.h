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
	vector<TexturePtr> tex;
	ShaderPtr shader;
public:
	Material();
	~Material();
	bool Init();
	bool RegTexture(string filename);
	bool InitShader(string filename);
	bool Bind(void);
};
typedef shared_ptr<Material> MaterialPtr;
#endif