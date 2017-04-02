#ifndef _RENDERCOMMAND_HPP
#define _RENDERCOMMAND_HPP
#pragma once
#include<Common.hpp>
#include <Mesh.h>
#include <Material.h>
class RenderEngine;

enum CommandType
{
	EMPTY,
	BIND_VAO,
	DRAW_MESH,
};

class RenderCommand
{
public:
	int type;
	RenderCommand() :type(EMPTY){};
	RenderCommand(int type) :type(type){};
	~RenderCommand(){};

	virtual void Do(RenderEngine * render);
	virtual void Before();
	virtual void Deal(RenderEngine * render);
	virtual void After();
};
class RcmdMesh:public RenderCommand
{
public:
	Mesh		*mesh;
	Material	*material;
	kmMat4 *transform;

public:
	RcmdMesh() :RenderCommand(DRAW_MESH){ };
	~RcmdMesh(){};

	void Init(Mesh *mesh, Material *material);
	void Deal(RenderEngine * render);

};

#endif

