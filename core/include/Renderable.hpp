#ifndef _RENDERABLE_HPP
#define _RENDERABLE_HPP
#pragma once
#include<Base.hpp>
class Renderable
{
public:
	Renderable();
	virtual ~Renderable();

	virtual void OnRenderBegin();
	virtual void OnRenderEnd();

	virtual void AddToRenderQueue();

	virtual void Render();
}
#endif
