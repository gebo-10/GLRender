#ifndef _COMP_MESH_RENDER_H
#define _COMP_MESH_RENDER_H
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
	struct MeshRenderItem
	{
		MaterialPtr material;
		MeshPtr		mesh;
	};
public:
	Model model;
	std::vector<MeshRenderItem> meshs;

	std::vector<RenderCommandPtr> cmd_list;

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
		
		MeshPtr new_mesh= std::make_shared<Mesh>();

		new_mesh->Init(model.scene->mMeshes[i]);


		App::Instance()->resource.GetRes(mtl, [=](ResPtr res) {
			MeshRenderItem item;
			item.material = static_pointer_cast<Material>(res);
			item.mesh = new_mesh;
			meshs.push_back(item);

			RcmdGeometryPtr cmd_geo = std::make_shared<RcmdGeometry>();
			cmd_geo->Init(new_mesh);

			RcmdMaterialPtr cmd_mtl = std::make_shared<RcmdMaterial>();
			cmd_mtl->Init(item.material);

			cmd_list.push_back(cmd_mtl);
			cmd_list.push_back(cmd_geo);
		});
	}

	
	
	
	
}

void CompMeshRender::Update(Uint32 delta)
{

	for (int i=0;i<cmd_list.size();i++)
	{
		RenderCommandPtr cmd = cmd_list[i];
		if (cmd->type== RCMD_GEOMETRY)
		{
			RcmdGeometryPtr cmd_geo = static_pointer_cast<RcmdGeometry>(cmd);
			cmd_geo->transform = &obj->transform;
		}
		App::Instance()->render.AddToCommandList(cmd.get());

	}

}

void CompMeshRender::OnMsg(int type)
{

}

#endif

