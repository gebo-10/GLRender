#include <RenderEngine.hpp>
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	vao.Init();
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

	vao.vbos.clear();//??是否需要清楚vbo clear是否 能清除显存的vbo
	for (int i = 0; i < command_list.size();i++)
	{
		Command cmd = command_list[i];
		switch (cmd.type)
		{
		case RenderEngine::BIND_VAO:
			break;
		case RenderEngine::DRAW_MESH:
		{
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();//保存摄像机矩阵
			glTranslatef(20*i, 0, -30);//构建 转移矩阵 并且与当前视图矩阵 结合 影响本次渲染
			Mesh * mesh = (Mesh *)cmd.arg;
			vao.NewVBO(mesh->vertex.size() * sizeof(float), (void *)&mesh->vertex[0]);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, true, 0, 0);

			vao.NewVBO(mesh->uv.size() * sizeof(float), (void *)&mesh->uv[0]);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

			vao.InitEBO(mesh->index.size() * sizeof(int), (void *)&mesh->index[0]);
			
			glDrawElements(GL_TRIANGLES, mesh->index.size(), GL_UNSIGNED_INT, 0);
			glPopMatrix();//恢复摄像机矩阵
		}
		break;

		default:
			LOG(WARNING) << "unknow cmd type:" << cmd.type  << endl;
			break;
		}
	}

	SDL_GL_SwapWindow(pWindow);
	OnRenderEnd();
}


bool RenderEngine::AddToCommandList(Command cmd)
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


