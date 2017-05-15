#ifndef _TEXTURE_H
#define _TEXTURE_H
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
	int width;
	int height;
public:
	Texture();
	~Texture();
	bool LoadCallback();
	bool InitFromMem(void * data, int width, int height);
	bool InitFromSurface(SDL_Surface * img);
	bool Init(string filename);
	void Bind(int shader, int texture_index, const char * name);
	void SetParam(int target, int name, int param);
};
typedef shared_ptr< Texture> TexturePtr;
#endif