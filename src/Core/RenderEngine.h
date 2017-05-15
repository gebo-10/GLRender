#ifndef _RENDERENGINE_H
#define _RENDERENGINE_H
#pragma once
#include<Base.hpp>
#include<vector>
#include <GL/glew.h>
#include <VAO.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <RenderCommand.h>
#include <Light.h>

#define MAX_LIGHT 10
#define MAX_CAMERA 10

class UniformBlock
{
public:
	float time;
	vec4 color;

	GLint offset[2];

	int block_size;
	GLuint uboHandle;
	GLubyte *buff;

	UniformBlock() {
		time = 1;
		color.x = 0.1;
		color.y = 0.5;
		color.z = 0.3;
		color.w = 1;
	};
	~UniformBlock() {};

	bool Init();
	bool Bind();
	
};

class LightInfo
{
public:
	Light *light;
	mat4 light_vp;
	LightInfo(Light * light) { this->light = light; };
	~LightInfo() {};
};

class PipeLineStatus
{
public:
	UniformBlock uniform_block;	
	Camera * camera;

	std::vector<LightInfo> lights;
	int max_light_num;
	int per_light_buff_size;
	void * lights_buff;
	GLuint light_ubo;


	MaterialPtr material;
	MaterialPtr shadow_material;

	

	//RenderTarget target;

	PipeLineStatus() {};
	~PipeLineStatus() {};

	bool Init() ;
	bool Bind() ;
};

class PassManager
{
public:
	PassManager() {};
	~PassManager() {};
};

class RenderEngine
{
public:

	PipeLineStatus pipeline_status;
	Camera * cameras[MAX_CAMERA];

	SDL_Window	*window;
	SDL_Renderer*renderer;
	SDL_GLContext context;

	VAO vao;


public:
	RenderEngine();
	~RenderEngine();

	bool Init(char * name, int width, int height);
	bool InitSecond();

	void Update(Uint32 delta);

	void OnRenderBegin();
	void OnRenderEnd();

	void ShadowStage();
	void RenderFrame();

	

	void RenderShadowMesh();
public:

	std::vector<RenderCommand * > command_list;

	bool AddToCommandList(RenderCommand *cmd);
	bool ClearCommandList();
	bool FreshCommandList();

public:
	void ShowDeviceInfo();
	int CatchError();

	void SetUniform(mat4 * model_matrix);
};
#endif
