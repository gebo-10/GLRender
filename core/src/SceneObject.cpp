#include <SceneObject.h>
#include <App.h>
SceneObject::SceneObject()
{
	tag = App::Instance()->scene.GenTag();
	name = "";
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
}

void SceneObject::AddComponent(Component *comp)
{
	comps.push_back(comp);
}