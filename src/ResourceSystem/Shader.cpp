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
				tmp.value.ptr = res; //???��̬ת�� ����ת��
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
	//������
	if (0 == vertex_shader)
	{
		LOG(ERROR) << "ERROR : Create vertex shader failed" << endl;
		return false;
	}

	//����ɫ��Դ�������ɫ�����������
	const GLchar *vCodeArray[1] = { source };
	glShaderSource(vertex_shader, 1, vCodeArray, NULL);

	//������ɫ������
	glCompileShader(vertex_shader);

	//�������Ƿ�ɹ�
	GLint compileResult;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//�õ�������־����
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//�õ���־��Ϣ�����
			glGetShaderInfoLog(vertex_shader, logLen, &written, log);
			LOG(ERROR) << "vertex shader compile log : " << log <<  endl;
			free(log);//�ͷſռ�
		}
		return false;
	}
	return true;
}

bool Shader::BuildFragShader(char * source)
{
	//������ɫ������Ƭ����ɫ��
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	//������
	if (0 == frag_shader)
	{
		LOG(ERROR) << "ERROR : Create fragment shader failed" << endl;
		return false;
	}

	//����ɫ��Դ�������ɫ�����������
	const GLchar *fCodeArray[1] = { source };
	glShaderSource(frag_shader, 1, fCodeArray, NULL);

	//������ɫ������
	glCompileShader(frag_shader);

	//�������Ƿ�ɹ�
	GLint compileResult;
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//�õ�������־����
		glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//�õ���־��Ϣ�����
			glGetShaderInfoLog(frag_shader, logLen, &written, log);
			LOG(ERROR) << "fragment shader compile log : " << log << endl;
			free(log);//�ͷſռ�
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
	//������ɫ������
	GLuint program = glCreateProgram();
	if (!program)
	{
		LOG(ERROR) << "ERROR : create program failed" << endl;
		return false;
	}
	//����ɫ���������ӵ��������ĳ�����
	glAttachShader(program, vertex_shader);
	glAttachShader(program, frag_shader);
	//����Щ�������ӳ�һ����ִ�г���
	glLinkProgram(program);
	//��ѯ���ӵĽ��
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
	//���ӳɹ�����OpenGL������ʹ����Ⱦ����
	LOG(INFO) << "build shader success" << endl;
	id = program;
	return true;
}
