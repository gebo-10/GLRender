#ifndef _RENDERENGINE_HPP
#define _RENDERENGINE_HPP
#pragma once
#include<Base.hpp>
#include<vector>
#include <GL/glew.h>
#include <VAO.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
class RenderEngine
{
public:
	SDL_Window	*pWindow;
	SDL_Renderer*pRenderer;
	SDL_GLContext glcontext;

	VAO vao;

public:
	RenderEngine();
	~RenderEngine();

	bool Init(char * name, int width, int height);
	void Update(Uint32 delta);

	void OnRenderBegin();
	void OnRenderEnd();

	void RenderFrame();

public:
	enum CommandType
	{
		BIND_VAO,
		DRAW_MESH,
	};
	struct Command{
		int type;
		void * arg;
	};

	std::vector<Command> command_list;
	bool AddToCommandList(Command cmd);
	bool ClearCommandList();
	bool FreshCommandList();
};
#endif
