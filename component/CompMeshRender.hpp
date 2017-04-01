#ifndef _COMP_MESH_RENDER_HPP
#define _COMP_MESH_RENDER_HPP
#pragma once
#include <Component.h>
#include <Mesh.h>
#include <Material.h>
#include <App.h>
#include <RenderCommand.h>
class CompMeshRender :public Component
{
public:
	Model model;
	Material material;
	vector<Mesh> meshs;

	RcmdMesh cmd;

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
	material.InitShader("vert.txt", "frag.txt");
	material.RegTexture("f.jpg");

	for (int i = 0; i < model.scene->mNumMeshes;i++)
	{
		Mesh new_mesh;
		new_mesh.Init(model.scene->mMeshes[i]);
		meshs.push_back(new_mesh);
	}

	cmd.Init(&meshs[0], &material);
}

void CompMeshRender::Update(Uint32 delta)
{
	App *app=App::Instance();
	app->render.AddToCommandList(&cmd);
	material.Bind();
}

void CompMeshRender::OnMsg(int type)
{

}

#endif

