#include <SceneObject.h>
SceneObject::SceneObject()
{

}

SceneObject::~SceneObject()
{

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
