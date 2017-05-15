#include <RenderEngine.h>
#include <Mesh.h>
#include <App.h>
RenderEngine::RenderEngine()
{

}

RenderEngine::~RenderEngine()
{

}

bool RenderEngine::Init(char * name,int width,int height)
{
	int win_width = width, win_height = height;


	// 1. initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL initialize fail:%s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// 2. create window
	window = SDL_CreateWindow(name,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (NULL == window)
	{
		printf("Create window fail:%s\n", SDL_GetError());
	}

	context = SDL_GL_CreateContext(window);
	renderer = SDL_CreateRenderer(window, -1, 0);
	glewInit();

	ShowDeviceInfo();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, 100.0);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(100.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	vao.Init();
	char memery[1024*100*5] = { 0 };
	vao.NewVBO(sizeof(memery), (void *)&memery);
	vao.NewVBO(sizeof(memery), (void *)&memery);
	vao.NewVBO(sizeof(memery), (void *)&memery);
	vao.NewVBO(sizeof(memery), (void *)&memery, GL_ELEMENT_ARRAY_BUFFER);

	glEnable(GL_BLEND);
	glHint(GL_LINE_SMOOTH, GL_NICEST);

	CatchError();
	return true;
}

bool RenderEngine::InitSecond()
{
	pipeline_status.Init();
	return true;
}

void RenderEngine::Update(Uint32 delta)
{
	//控制间隔时间
	//LOG(INFO) << delta;
	RenderFrame();
}

void RenderEngine::OnRenderBegin()
{
	CatchError();
}

void RenderEngine::OnRenderEnd()
{
	pipeline_status.lights.clear();
	ClearCommandList();
	CatchError();
}

void RenderEngine::ShadowStage()
{
	Camera light_camera;

	pipeline_status.material = pipeline_status.shadow_material;
	pipeline_status.material->Bind();
	pipeline_status.uniform_block.Bind();

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.0, 4.0);
	for (int i = 0; i < pipeline_status.lights.size(); i++) //生成shadow map
	{
		LightInfo &light_info = pipeline_status.lights[i];
		Light *light = light_info.light;

		light_camera.Init(light->pos, light->target);
		light_camera.SetViewPort(light->shadow_width,light->shadow_height);
		light_camera.SetModelViewMatrix();
		

		mat4 matv;
		mat4 matp;
		glGetFloatv(GL_MODELVIEW_MATRIX, matv.mat);
		glGetFloatv(GL_PROJECTION_MATRIX, matp.mat);
		kmMat4Multiply(&light_info.light_vp, &matp, &matv);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, light_info.light->fbo);
		glClear(GL_DEPTH_BUFFER_BIT);

		RenderShadowMesh();

	}
	glDisable(GL_POLYGON_OFFSET_FILL);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
void RenderEngine::RenderFrame()
{
	GLenum err;
	
	OnRenderBegin();

	ShadowStage();
	
	pipeline_status.Bind();
	pipeline_status.uniform_block.Bind();
	pipeline_status.material->Bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	for (int i = 0; i < command_list.size();i++)
	{
		RenderCommand * cmd = command_list[i];
		cmd->Do(this);

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE10 );

		glBindTexture(GL_TEXTURE_2D, pipeline_status.lights[0].light->shadow_map);

		glUniform1i(glGetUniformLocation(pipeline_status.material->shader->id, "shadow_map"), 10);
	}

	SDL_GL_SwapWindow(window);
	OnRenderEnd();
}

void RenderEngine::RenderShadowMesh()
{
	//渲染 需要阴影的模型
	for (int i = 0; i < command_list.size(); i++)
	{
		RenderCommand * cmd = command_list[i];
		if (cmd->type == RCMD_GEOMETRY)
		{
			RcmdGeometry * cmd_mesh = (RcmdGeometry *)cmd;
			if (cmd_mesh->shadow_type > 0)
			{
				cmd->Do(this);
			}

		}
	}
}

int  RenderEngine::CatchError()
{
	int num = 0;
	for (GLenum err; (err = glGetError()) != GL_NO_ERROR;)
	{
		num++;
		switch (err)
		{
		case GL_INVALID_ENUM:
			LOG(ERROR)<<"opengl error: "<< ("GL Invalid Enum\n");
			break;
		case GL_INVALID_VALUE:
			LOG(ERROR) << "opengl error: " << ("GL Invalid Value\n");
			break;
		case GL_INVALID_OPERATION:
			LOG(ERROR) << "opengl error: " << ("GL Invalid Operation\n");
			break;
		case GL_OUT_OF_MEMORY:
			LOG(ERROR) << "opengl error: " << ("GL Out Of Memory\n");
			break;
			//case GL_INVALID_FRAMEBUFFER_OPERATION:  
			//  return ("GL Invalid FrameBuffer Operation\n");  
		case  GL_STACK_OVERFLOW:
			LOG(ERROR) << "opengl error: " << ("GL Stack Overflow\n");
			break;
		case GL_STACK_UNDERFLOW:
			LOG(ERROR) << "opengl error: " << ("GL Stack Underflow\n");
			break;
			//case GL_TABLE_TOO_LARGE:  
			//  return ("GL Table Too Large\n");  
		default:
			LOG(ERROR) << "opengl error: unknow :s "<< err;
		};
	}
	return num;
}

bool RenderEngine::AddToCommandList(RenderCommand * cmd)
{
	switch (cmd->type)
	{
	case RCMD_LIGHT:
	case RCMD_CAMERA:
		cmd->Do(this);
		break;
	default:
		command_list.push_back(cmd);
		break;
	}
	return true;
}

bool RenderEngine::ClearCommandList()
{
	command_list.clear();
	return true;
}

bool RenderEngine::FreshCommandList()
{
	return true;
}

void RenderEngine::ShowDeviceInfo()
{
	//1、查看GLSL和OpenGL的版本
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion =
	glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << "GL Vendor    :" << vendor << endl;
	cout << "GL Renderer  : " << renderer << endl;
	cout << "GL Version (string)  : " << version << endl;
	cout << "GL Version (integer) : " << major << "." << minor << endl;
	cout << "GLSL Version : " << glslVersion << endl;
}

void RenderEngine::SetUniform(mat4 * model_matrix)
{
	mat4 matp;
	mat4 matm= *model_matrix;
	mat4 matmv;
	mat4 matmvp;
	glGetFloatv(GL_MODELVIEW_MATRIX, matmv.mat);
	glGetFloatv(GL_PROJECTION_MATRIX, matp.mat);

	kmMat4Multiply(&matmvp, &matp, &matmv);

	MaterialPtr material = this->pipeline_status.material;

	int localp	= glGetUniformLocation(material->shader->id, "P");
	int localm	= glGetUniformLocation(material->shader->id, "M");
	int localmv = glGetUniformLocation(material->shader->id, "MV");
	int localmvp= glGetUniformLocation(material->shader->id, "MVP");


	glUniformMatrix4fv(localp,	1, GL_FALSE, matp.mat);
	glUniformMatrix4fv(localm,	1, GL_FALSE, matm.mat);
	glUniformMatrix4fv(localmv, 1, GL_FALSE, matmv.mat);
	glUniformMatrix4fv(localmvp,1, GL_FALSE, matmvp.mat);

	int locallvp = glGetUniformLocation(material->shader->id, "light_VP");
	glUniformMatrix4fv(locallvp, 1, GL_FALSE, pipeline_status.lights[0].light_vp.mat);
}

////////////////////////////////////////////////////////////////////////////
bool UniformBlock::Init()
{
	offset[0] = 0;
	offset[1] =4* sizeof(GLfloat);

	block_size=8* sizeof(GLfloat);

	buff = (GLubyte*)malloc(block_size);
	glGenBuffers(1, &uboHandle);
	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
	glBufferData(GL_UNIFORM_BUFFER, block_size, buff, GL_STATIC_DRAW);

	//bind the UBO th the uniform block  
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboHandle);//绑定第0个 节点 

	return true;
}
bool UniformBlock::Bind()
{

	memcpy(buff + offset[0], (void *)&time, sizeof(GLfloat));
	memcpy(buff + offset[1], (void *)&color, 4 * sizeof(GLfloat));

	//create OpenGL buffer UBO to store the data  
	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, block_size, buff);
	
	return true;
}
//////////////////////////////////////////////////////////////////////////////////
bool PipeLineStatus::Init()
{
	ResPtr res=App::Instance()->resource.GetResSync("System/shadow_map.mtl");
	this->shadow_material = static_pointer_cast<Material>(res);

	uniform_block.Init();
	max_light_num=10;
	per_light_buff_size=36 * sizeof(GLfloat);
	lights_buff = malloc(max_light_num* per_light_buff_size);

	glGenBuffers(1, &light_ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, light_ubo);
	glBufferData(GL_UNIFORM_BUFFER, max_light_num* per_light_buff_size, lights_buff, GL_STATIC_DRAW);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	//bind the UBO th the uniform block  
	//glBindBufferBase(GL_UNIFORM_BUFFER, 0, light_ubo);//绑定第0个 节点 

	return true;
}

bool PipeLineStatus::Bind()
{
	camera->SetModelViewMatrix();
	material->Bind();
	uniform_block.Bind();

	memset(lights_buff, 0, per_light_buff_size * max_light_num);
	for (int i=0;i<lights.size();i++)
	{
		int offset = i*per_light_buff_size;
		GPULight *gpu_light = lights[i].light->GetGpuLightStruct();
		gpu_light->dir = vec4({ 0, 0, 1, 0 });
		gpu_light->index = i;
		gpu_light->VP = lights[i].light_vp;
		memcpy((char *)lights_buff + offset,(void *) gpu_light, per_light_buff_size);

		float b[1000] = { 0 };
		float * a = (float *)lights_buff;
		
		for (int i = 0; i < per_light_buff_size; i++)
		{
			b[i] = a[i];
		}
int c = sizeof(GPULight);
	}

	
	glBindBuffer(GL_UNIFORM_BUFFER, light_ubo);

	glBufferSubData(GL_UNIFORM_BUFFER, 0, max_light_num* per_light_buff_size, lights_buff);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, light_ubo);//绑定第n个 节点 

	return true;
}
///////////////////////////////////////////////////////////////
