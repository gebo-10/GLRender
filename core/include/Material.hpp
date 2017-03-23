#ifndef _METARIAL_HPP
#define _METARIAL_HPP
#pragma once
#include <vector>
#include <ShaderProgram.hpp>
#include <Texture.hpp>
class Metarial
{
public:
	vector<Texture *> tex;
	ShaderProgram shader;
public:
	Metarial();
	~Metarial();
	bool regTexture(char * file);
	bool initShader(GLchar *vShaderFile, GLchar *fShaderFile);
	bool bind(void);
};
Metarial::Metarial(){

}
Metarial::~Metarial(){

}
bool Metarial::initShader(GLchar *vShaderFile, GLchar *fShaderFile){
	shader.buildShader(vShaderFile, fShaderFile);
	return true;
}
bool Metarial::regTexture(char * file){
	Texture *new_tex = new Texture(file);
	tex.push_back(new_tex);
	return true;
}
bool Metarial::bind(){
	for (int i = 0; i < tex.size(); i++){
		char name[64] = { 0 };
		sprintf(name, "tex%d", i);
		tex[i]->bind(shader.id, i, name);
	}
	glUseProgram(shader.id);
	return true;
}
#endif