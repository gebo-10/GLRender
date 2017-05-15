#include <Material.h>
#include <App.h>
#include <Json.h>

Material::Material(){
	shader=App::Instance()->resource.GetDefaultShader();
}
Material::~Material(){

}

bool Material::LoadCallback()
{
	using namespace rapidjson;
	Document d;
	char *p = (char *)buff;
	d.Parse((char *)buff);

	Value& shader = d["shader"];
	App::Instance()->resource.GetRes(shader.GetString(), [=](ResPtr res) {
		this->shader = static_pointer_cast<Shader>(res);
		
		this->ParseParam((char *)buff);
	});

	return true;
}

bool Material::Bind() {
	glUseProgram(shader->id);
	int texture_count=0;
	ShaderParam * pparam = NULL;
	for (int i=0;i<param.size() ; i++)
	{
		pparam = &param[i];
		int local = glGetUniformLocation(shader->id, pparam->param_name.c_str());
		switch (pparam->type)
		{
		case SPT_BOOL:
			glUniform1i(local, pparam->value.b ? 1:0);
			break;
		case SPT_INT:
			glUniform1i(local, pparam->value.i);
			break;
		case SPT_FLOAT:
			glUniform1f(local, pparam->value.f);
			break;
		case SPT_COLOR:
			Color color = pparam->value.color;
			glUniform4f(local, color.r, color.g,color.b,color.a);
			break;
		case SPT_TEXTURE:
			TexturePtr texture= static_pointer_cast<Texture>(pparam->value.ptr);
			texture->Bind(shader->id, texture_count++, pparam->param_name.c_str());
			break;
		}
		
	}

	return true;
}

bool Material::ParseParam(char * jsonstr)
{
	param.clear();

	using namespace rapidjson;
	Document d;
	d.Parse(jsonstr);

	Value& param_list = d["param"];
	for (int i = 0; i < param_list.Size(); i++)
	{
		Value & item = param_list[i];
		ShaderParam param;
		param.param_name = item[0].GetString();
		param.editor_name = item[1].GetString();

		string type = item[2].GetString();

		/////////////////////////////////////////////////////////////////////////////
		if (type == "texture")
		{
			param.type = SPT_TEXTURE;
			param.value.ptr = App::Instance()->resource.GetDefaultTexure();
			App::Instance()->resource.GetRes(item[3].GetString(), [=](ResPtr res) {
				ShaderParam tmp = param;
				tmp.value.ptr = res; //???动态转换 向下转换
				this->param.push_back(tmp);
			});
			continue;
		}
		////////////////////////////////////////////////////////////////////////////////
		if (type == "int")
		{
			param.type = SPT_INT;
			param.value.i = item[3].GetInt();
		}
		else if (type == "float")
		{
			param.type = SPT_FLOAT;
			param.value.f = item[3].GetFloat();
		}
		else if (type == "bool")
		{
			param.type = SPT_BOOL;
			param.value.b = item[3].GetBool();
		}
		else if (type == "color")
		{
			param.type = SPT_COLOR;
			param.value.color.r = item[3][0].GetFloat();
			param.value.color.g = item[3][1].GetFloat();
			param.value.color.b = item[3][2].GetFloat();
			param.value.color.a = item[3][3].GetFloat();
		}
		
		this->param.push_back(param);

	}

	return true;
}

