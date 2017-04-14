#include <SceneObject.h>
#include <App.h>
SceneObject::SceneObject()
{
	tag = App::Instance()->scene.GenTag();
	name = "";
	parent = NULL;
	
	kmVec3Fill(&position, 0, 0, 0);
	kmVec3Fill(&scale, 1, 1, 1);
	kmVec3Fill(&rotate, 0, 0, 0);
	kmMat4Identity(&transform);

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
	kmMat4 tmp;
	kmMat4 tmp2;
	kmMat4Identity(&tmp);
	kmMat4Identity(&tmp2);
	kmMat4Identity(&transform);

	if (parent != NULL)
	{
		transform = parent->transform;
		//tmp = transform;
		//kmMat4Multiply(&transform, &parent->transform, &tmp);
	}



	kmMat4Translation(&tmp, position.x, position.y, position.z);
	kmMat4Multiply(&transform, &transform, &tmp);

	kmMat4Scaling(&tmp, scale.x, scale.y, scale.z);
	kmMat4Multiply(&transform, &transform, &tmp);

	kmMat4RotationX(&tmp, rotate.x);
	kmMat4Multiply(&transform, &transform, &tmp);

	kmMat4RotationY(&tmp, rotate.y);
	kmMat4Multiply(&transform, &transform, &tmp);

	kmMat4RotationZ(&tmp, rotate.z);
	kmMat4Multiply(&transform, &transform, &tmp);

	

	
}


void SceneObject::AddComponent(Component *comp)
{
	comp->SetBelong(this);
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
