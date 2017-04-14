#ifndef _RENDERCOMMAND_HPP
#define _RENDERCOMMAND_HPP
#pragma once
#include<Common.h>
#include <Mesh.h>
#include <Material.h>
#include <kazmath.h>
class RenderEngine;

enum CommandType
{
	EMPTY,
	BIND_VAO,
	DRAW_MESH,
	DRAW_LINES,
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

class RcmdLine :public RenderCommand
{
public:
	Material	*material;
	vector <kmVec3> vertex;
	Color		color;

public:
	RcmdLine() :RenderCommand(DRAW_LINES){ };
	~RcmdLine(){};

	void Init(vector <kmVec3> vertex, Color color);
	void Deal(RenderEngine * render);

};

#endif

