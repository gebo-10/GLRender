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
	RCMD_EMPTY,
	RCMD_BIND_VAO,
	RCMD_DRAW_MESH,
	RCMD_DRAW_LINES,
	RCMD_LIGHT,
};

class RenderCommand
{
public:
	int type;
	int status; //已经创建 已经初始化 已经销毁
	RenderCommand() :type(RCMD_EMPTY){};
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
	int		shadow_type;//0 表示没阴影， 1 表示硬阴影，  2 表示软阴影
	Mesh		*mesh;
	MaterialPtr	material;
	kmMat4 *transform;

public:
	RcmdMesh() :RenderCommand(RCMD_DRAW_MESH){ };
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
	RcmdLine() :RenderCommand(RCMD_DRAW_LINES){ };
	~RcmdLine(){};

	void Init(vector <kmVec3> vertex, Color color);
	void Deal(RenderEngine * render);

};

////////////////////////////////////////////////////////////////////////
class RcmdShadowMap :public RenderCommand
{
public:
	GLuint m_fbo;
	GLuint m_shadowMap;

	ShaderPtr shader;

public:
	RcmdShadowMap() :RenderCommand(RCMD_LIGHT) { };
	~RcmdShadowMap() {};

	void Init();
	void Deal(RenderEngine * render);

};

#endif

