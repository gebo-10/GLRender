#ifndef _FONT_H
#define _FONT_H
#pragma once
#include<Base.hpp>


#include <ft2build.h>
#include <freetype/ftoutln.h>
#include <freetype/freetype.h>  
#include <freetype/ftglyph.h>  
#include <freetype/ftoutln.h>  
#include <freetype/fttrigon.h> 
#include FT_FREETYPE_H

#include <Texture.h>

class Font{
public:
	FT_Library	library;
	FT_Face		face;
	FT_Error	error;
	
	int   size;

	Font();
	~Font();
	bool Init();
	void SetFont(const char* font_file);
	void SetFontSize(int size);
	TexturePtr GetStrTexture(string str);

};
#endif