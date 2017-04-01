#include <SceneObject.h>
#include <App.h>
SceneObject::SceneObject()
{
	tag = App::Instance()->scene.GenTag();
	name = "";
	parent = NULL;
	comps.clear();
}

SceneObject::~SceneObject()
{
	for (Uint32 i = 0; i < comps.size(); i++)
	{
		delete comps[i];
	}
	comps.clear();
}

void SceneObject::Update(Uint32 delta)
{
	for (Uint32 i = 0; i < comps.size(); i++)
	{
		comps[i]->Update(delta);
	}
	UpdateTransform();
}


void SceneObject::UpdateTransform()
{
	kmMat4Translation(&transform, 0, 0, 0);
}


void SceneObject::AddComponent(Component *comp)
{
	comps.push_back(comp);
}

Component * SceneObject::GetComponent(int tag)
{
	for (Uint32 i = 0; i < comps.size(); i++)
	{
		if (comps[i]->tag == tag)
		{
			return comps[i];
		}
	}
	return NULL;
}

Component * SceneObject::GetComponent(string name)
{
	for (Uint32 i = 0; i < comps.size(); i++)
	{
		if (comps[i]->name == name)
		{
			return comps[i];
		}
	}
	return NULL;
}
