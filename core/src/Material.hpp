#ifndef _METARIAL_HPP
#define _METARIAL_HPP
#pragma once
#include <vector>
#include <ShaderProgram.hpp>
#include <Texture.hpp>
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
Material::Material(){

}
Material::~Material(){

}
bool Material::InitShader(GLchar *vShaderFile, GLchar *fShaderFile){
	shader.buildShader(vShaderFile, fShaderFile);
	return true;
}
bool Material::RegTexture(char * file){
	Texture *new_tex = new Texture(file);
	tex.push_back(new_tex);
	return true;
}
bool Material::Bind(){
	for (int i = 0; i < tex.size(); i++){
		char name[64] = { 0 };
		sprintf(name, "tex%d", i);
		tex[i]->bind(shader.id, i, name);
	}
	glUseProgram(shader.id);
	return true;
}
#endif