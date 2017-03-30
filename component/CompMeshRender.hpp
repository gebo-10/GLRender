#ifndef _COMP_MESH_RENDER_HPP
#define _COMP_MESH_RENDER_HPP
#pragma once
#include <Component.h>
#include <Mesh.h>
#include <Material.hpp>
#include <App.h>
class CompMeshRender :public Component
{
public:
	Model model;
	Material metarial;
	vector<Mesh> meshs;

	CompMeshRender();
	~CompMeshRender();
	void Init(char *filename);
	void Update(Uint32 delta);

	void OnMsg(int type);
};

CompMeshRender::CompMeshRender()
{
	meshs.clear();
}

CompMeshRender::~CompMeshRender()
{

}

void CompMeshRender::Init(char *filename)
{
	model.Import(filename);
	metarial.InitShader("vert.txt", "frag.txt");
	metarial.RegTexture("f.jpg");

	for (int i = 0; i < model.scene->mNumMeshes;i++)
	{
		Mesh new_mesh;
		new_mesh.Init(model.scene->mMeshes[i]);
		meshs.push_back(new_mesh);
	}
}

void CompMeshRender::Update(Uint32 delta)
{
	App *app=App::Instance();
	RenderEngine::Command cmd;
	cmd.type = RenderEngine::DRAW_MESH;
	cmd.arg = (void *)&meshs[0];
	app->render.AddToCommandList(cmd);
	metarial.Bind();
}

void CompMeshRender::OnMsg(int type)
{

}

#endif

