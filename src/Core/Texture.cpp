#include <Texture.h>
#include <Base.hpp>
Texture::Texture(char *file){
	init(file);
}
Texture::~Texture(){
}
void Texture::init(char *file){
	img = IMG_Load(file);
	if (img==NULL)
	{
		LOG(ERROR) << "Texure init ,image not exist: " << file;
	}
	img = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_ABGR8888, 0);

	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

void Texture::bind(int shader, int texture_index, char * name){
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0 + texture_index);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glUniform1f(glGetUniformLocation(shader, name), 0);
}