#ifndef _RENDERENGINE_HPP
#define _RENDERENGINE_HPP
#pragma once
#include<Base.hpp>
class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();

	void OnRenderBegin();
	void OnRenderEnd();

	void AddToRenderQueue();

	void Render();
}
#endif
