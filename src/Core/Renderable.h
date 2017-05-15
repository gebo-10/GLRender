#ifndef _RENDERABLE_H
#define _RENDERABLE_H
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
