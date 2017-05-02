#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP
#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>

#include <ResItem.h>
class Texture:public ResItem
{
public:
	SDL_Surface * img;
	GLuint tex_id ;
public:
	Texture();
	~Texture();
	bool Init();
	bool Init(string filename);
	void Bind(int shader, int texture_index, const char * name);
	void SetParam(int target, int name, int param);
};
typedef shared_ptr< Texture> TexturePtr;
#endif