#include <RenderEngine.h>
#include <Mesh.h>
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
	pWindow = SDL_CreateWindow(name,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (NULL == pWindow)
	{
		printf("Create window fail:%s\n", SDL_GetError());
	}

	glcontext = SDL_GL_CreateContext(pWindow);
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	glewInit();

	ShowDeviceInfo();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, 10.0);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(10.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	vao.Init();
	char memery[1024*100*5] = { 0 };
	vao.NewVBO(sizeof(memery), (void *)&memery);
	vao.NewVBO(sizeof(memery), (void *)&memery);
	vao.NewVBO(sizeof(memery), (void *)&memery, GL_ELEMENT_ARRAY_BUFFER);
	CatchError();
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
	ClearCommandList();
	CatchError();
}

void RenderEngine::RenderFrame()
{
	GLenum err;
	
	OnRenderBegin();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < command_list.size();i++)
	{
		RenderCommand * cmd = command_list[i];
		cmd->Do(this);
	}

	SDL_GL_SwapWindow(pWindow);
	OnRenderEnd();
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
	command_list.push_back(cmd);
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

