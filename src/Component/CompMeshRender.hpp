#ifndef _COMP_MESH_RENDER_HPP
#define _COMP_MESH_RENDER_HPP
#pragma once
#include <Base.hpp>
#include <Component.h>
#include <Mesh.h>
#include <Material.h>
#include <App.h>
#include <RenderCommand.h>
class CompMeshRender :public Component
{
public:
	Model model;
	MaterialPtr material;
	vector<Mesh> meshs;

	RcmdMesh cmd;

	CompMeshRender();
	~CompMeshRender();
	void Init(char *filename, char * mtl);
	void Update(Uint32 delta);

	void OnMsg(int type);
};

typedef shared_ptr<CompMeshRender> CompMeshRenderPtr;

CompMeshRender::CompMeshRender()
{
	meshs.clear();
}

CompMeshRender::~CompMeshRender()
{
	LOG(INFO) << "CompMeshRender delete" ;
}

void CompMeshRender::Init(char *filename,char * mtl)
{
	model.Import(filename);
	
	for (int i = 0; i < model.scene->mNumMeshes;i++)
	{
		Mesh new_mesh;
		new_mesh.Init(model.scene->mMeshes[i]);
		meshs.push_back(new_mesh);
	}

	App::Instance()->resource.GetRes(mtl,[=](ResPtr res) {
		material = static_pointer_cast<Material>(res);
		cmd.Init(&meshs[0], material);
	});
	
	
	
}

void CompMeshRender::Update(Uint32 delta)
{
	if (!cmd.CmdInited() || material->shader==nullptr )
	{
		return;
	}
	
	App *app=App::Instance();
	cmd.transform = &obj->transform;
	app->render.AddToCommandList(&cmd);
	material->Bind();
}

void CompMeshRender::OnMsg(int type)
{

}

#endif

