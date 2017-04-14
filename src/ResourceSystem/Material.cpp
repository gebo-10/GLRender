#include <Material.h>
#include <App.h>
Material::Material(){

}
Material::~Material(){

}
bool Material::InitShader(string filename){
	App::Instance()->resource.GetRes(filename, [=](ResPtr res) {
		shader = dynamic_pointer_cast<Shader>(res);
	});
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
		tex[i]->bind(shader->id, i, name);
	}
	glUseProgram(shader->id);
	return true;
}