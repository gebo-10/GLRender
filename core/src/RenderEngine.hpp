#ifndef _RENDERENGINE_HPP
#define _RENDERENGINE_HPP
#pragma once
#include<Base.hpp>
#incldue<vector>

class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();

	bool Start();

	void OnRenderBegin();
	void OnRenderEnd();

	void Render();

public:

	struct Command{
		int type;
		void * arg;
	};

	std::vector<Command> command_list;
	bool AddToCommandList(Command cmd);
	bool ClearCommandList();
	bool FreshCommandList();
}
#endif
