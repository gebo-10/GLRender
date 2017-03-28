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

	void AddToRenderQueue();

	void Render();

public:

	struct Command{
		int type;
		void * arg;
	};

	std::vector<Command> command_list;
	bool AddToCommandList(Command cmd);
	bool Fresh();
	bool Clear();

}
#endif
