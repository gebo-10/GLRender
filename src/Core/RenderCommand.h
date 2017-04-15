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
	int status; //已经创建 已经初始化 已经销毁
	RenderCommand() :type(EMPTY){};
	RenderCommand(int type) :type(type){};
	~RenderCommand(){};

	virtual void Do(RenderEngine * render);
	virtual void Before();
	virtual void Deal(RenderEngine * render);
	virtual void After();

	void ChangeStatus(int status) { this->status = status; };
	bool CmdInited() { return status == OBJ_INITED; }
};
class RcmdMesh:public RenderCommand
{
public:
	Mesh		*mesh;
	MaterialPtr	material;
	kmMat4 *transform;

public:
	RcmdMesh() :RenderCommand(DRAW_MESH){ };
	~RcmdMesh(){};

	void Init(Mesh *mesh, MaterialPtr material);
	void Deal(RenderEngine * render);

};

class RcmdLine :public RenderCommand
{
public:
	MaterialPtr material;
	vector <kmVec3> vertex;
	Color		color;

public:
	RcmdLine() :RenderCommand(DRAW_LINES){ };
	~RcmdLine(){};

	void Init(vector <kmVec3> vertex, Color color);
	void Deal(RenderEngine * render);

};

#endif

