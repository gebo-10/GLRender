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

	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, 10.0);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(10.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	vao.Init();
	char memery[1024*1] = { 0 };
	vao.NewVBO(sizeof(memery), (void *)&memery);
	vao.NewVBO(sizeof(memery), (void *)&memery);
	vao.NewVBO(sizeof(memery), (void *)&memery, GL_ELEMENT_ARRAY_BUFFER);
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

}

void RenderEngine::OnRenderEnd()
{
	ClearCommandList();
}

void RenderEngine::RenderFrame()
{
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


