#include <Material.h>
#include <App.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>



Material::Material(){
	shader=App::Instance()->resource.GetDefaultShader();
}
Material::~Material(){

}

bool Material::Init()
{
	using namespace rapidjson;
	Document d;
	char *p = (char *)buff;
	d.Parse((char *)buff);

	Value& shader = d["shader"];
	InitShader(shader.GetString());

	Value& texure = d["texure"];
	RegTexture(texure.GetString());

	
	return true;
}

bool Material::InitShader(string filename){
	App::Instance()->resource.GetRes(filename, [=](ResPtr res) {
		this->shader = static_pointer_cast<Shader>(res);
	});
	return true;
}
bool Material::RegTexture(string filename){
	App::Instance()->resource.GetRes(filename, [=](ResPtr res) {
		this->tex.push_back(static_pointer_cast<Texture>(res));
	});
	return true;
}
bool Material::Bind() {
	
	for (int i = 0; i < tex.size(); i++){
		char name[64] = { 0 };
		sprintf(name, "tex%d", i);
		tex[i]->Bind(shader->id, i, name);
	}
	
	glUseProgram(shader->id);
	return true;
}