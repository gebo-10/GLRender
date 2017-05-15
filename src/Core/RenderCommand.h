#ifndef _RENDERCOMMAND_H
#define _RENDERCOMMAND_H
#pragma once
#include<Common.h>
#include <Mesh.h>
#include <Material.h>
#include <kazmath.h>
#include <Light.h>
#include <Camera.h>
class RenderEngine;

enum CommandType
{
	RCMD_EMPTY,
	RCMD_BIND_VAO,
	RCMD_DRAW_MESH,
	RCMD_DRAW_LINES,
	RCMD_LIGHT,
	RCMD_GEOMETRY,
	RCMD_MATERIAL,
	RCMD_CAMERA,
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

typedef std::shared_ptr<RenderCommand> RenderCommandPtr;

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
typedef std::shared_ptr<RcmdMesh> RcmdMeshPtr;

///////////////////////////////////////////////////////////////////////////
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

typedef std::shared_ptr<RcmdLine> RcmdLinePtr;

////////////////////////////////////////////////////////////////////////
class RcmdShadowMap :public RenderCommand
{
public:
	GLuint m_fbo;
	GLuint m_shadowMap;

	ShaderPtr shader;

public:
	RcmdShadowMap() :RenderCommand(RCMD_EMPTY) { };
	~RcmdShadowMap() {};

	void Init();
	void Deal(RenderEngine * render);

};
typedef std::shared_ptr<RcmdShadowMap> RcmdShadowMapPtr;

////////////////////////////////////////////////////////////////////////////////
class RcmdGeometry :public RenderCommand
{
public:
	int			shadow_type;//0 表示没阴影， 1 表示硬阴影，  2 表示软阴影
	MeshPtr		mesh;
	mat4		*transform;

public:
	RcmdGeometry() :RenderCommand(RCMD_GEOMETRY) {
		shadow_type = 1;
	};
	~RcmdGeometry() {};

	void Init(MeshPtr mesh);
	void Deal(RenderEngine * render);

};
typedef std::shared_ptr<RcmdGeometry> RcmdGeometryPtr;

////////////////////////////////////////////////////////////////////////////////
class RcmdMaterial :public RenderCommand
{
public:
	MaterialPtr material;

public:
	RcmdMaterial() :RenderCommand(RCMD_MATERIAL) { };
	~RcmdMaterial() {};

	void Init(MaterialPtr material);
	void Deal(RenderEngine * render);

};
typedef std::shared_ptr<RcmdMaterial> RcmdMaterialPtr;

/////////////////////////////////////////////////////////////
class RcmdLight :public RenderCommand
{
public:
	Light * light;

public:
	RcmdLight() :RenderCommand(RCMD_LIGHT) { };
	~RcmdLight() {};

	void Init(Light * light);
	void Deal(RenderEngine * render);

};
typedef std::shared_ptr<RcmdLight> RcmdLightPtr;

/////////////////////////////////////////////////////////////
class RcmdCamera :public RenderCommand
{
public:
	Camera * camera;

public:
	RcmdCamera() :RenderCommand(RCMD_CAMERA) { };
	~RcmdCamera() {};

	void Init(Camera * camera) ;
	void Deal(RenderEngine * render) ;

};
typedef std::shared_ptr<RcmdCamera> RcmdCameraPtr;

#endif

