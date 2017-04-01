#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP
#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
class Texture
{
public:
	SDL_Surface * img;
	GLuint tex_id ;
	


public:
	Texture(char * file);
	~Texture();
	void init(char * file);
	void bind(int shader, int texture_index, char * name);
};

#endif