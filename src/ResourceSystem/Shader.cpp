#include <Shader.h>
#include <ResourceManager.h>
#include <App.h>
#include <Json.h>

Shader::Shader()
{
	vertex_shader = 0; 
	frag_shader = 0;
}

Shader::~Shader()
{
	cout << "shader delete:"<<filename << endl;
}

bool Shader::Init()
{
	char * p= (char*)buff;

	p = strtok((char*)buff, "@");
	this->ParseParam(p);

	p = strtok(NULL,"@");
	this->BuildVertexShader(p);
	
	p = strtok(NULL, "@");
	this->BuildFragShader(p);

	this->BuildProgram();
	delete buff;
	buff = NULL;
	return true;
}

bool Shader::ParseParam(char * jsonstr)
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
			return true;
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

void Shader::BuildShader(GLchar * vertex_file, GLchar * frag_file)
{
	App::Instance()->resource.GetRes(vertex_file, [=](ResPtr res) {
		this->BuildVertexShader((char *)res->buff);
		this->BuildProgram();
	});
	App::Instance()->resource.GetRes(frag_file, [=](ResPtr res) {
		this->BuildFragShader((char *)res->buff);
		this->BuildProgram();
	});
}

bool Shader::BuildVertexShader(char * source)
{
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	//错误检测
	if (0 == vertex_shader)
	{
		LOG(ERROR) << "ERROR : Create vertex shader failed" << endl;
		return false;
	}

	//把着色器源代码和着色器对象相关联
	const GLchar *vCodeArray[1] = { source };
	glShaderSource(vertex_shader, 1, vCodeArray, NULL);

	//编译着色器对象
	glCompileShader(vertex_shader);

	//检查编译是否成功
	GLint compileResult;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//得到编译日志长度
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//得到日志信息并输出
			glGetShaderInfoLog(vertex_shader, logLen, &written, log);
			LOG(ERROR) << "vertex shader compile log : " << log <<  endl;
			free(log);//释放空间
		}
		return false;
	}
	return true;
}

bool Shader::BuildFragShader(char * source)
{
	//创建着色器对象：片断着色器
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	//错误检测
	if (0 == frag_shader)
	{
		LOG(ERROR) << "ERROR : Create fragment shader failed" << endl;
		return false;
	}

	//把着色器源代码和着色器对象相关联
	const GLchar *fCodeArray[1] = { source };
	glShaderSource(frag_shader, 1, fCodeArray, NULL);

	//编译着色器对象
	glCompileShader(frag_shader);

	//检查编译是否成功
	GLint compileResult;
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//得到编译日志长度
		glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//得到日志信息并输出
			glGetShaderInfoLog(frag_shader, logLen, &written, log);
			LOG(ERROR) << "fragment shader compile log : " << log << endl;
			free(log);//释放空间
		}
		return false;
	}
	return true;
}

bool Shader::BuildProgram()
{
	if (vertex_shader ==0 || frag_shader==0)
	{
		return false;
	}
	//创建着色器程序
	GLuint program = glCreateProgram();
	if (!program)
	{
		LOG(ERROR) << "ERROR : create program failed" << endl;
		return false;
	}
	//将着色器程序链接到所创建的程序中
	glAttachShader(program, vertex_shader);
	glAttachShader(program, frag_shader);
	//将这些对象链接成一个可执行程序
	glLinkProgram(program);
	//查询链接的结果
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (GL_FALSE == linkStatus)
	{
		LOG(ERROR) << "ERROR : link shader program failed" << endl;
		GLint logLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH,&logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(program, logLen,
				&written, log);
			LOG(ERROR) << "Program log : " <<log << endl;
		}
		return false;
	}
	//链接成功，在OpenGL管线中使用渲染程序
	LOG(INFO) << "build shader success" << endl;
	id = program;
	return true;
}
