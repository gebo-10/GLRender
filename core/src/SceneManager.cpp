#include<SceneManager.h>
SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Init(RenderEngine *render)
{
	root = new SceneObject;
	this->render = render;
}

void SceneManager::Update(Uint32 delta)
{
	VistObj(root,delta);
}

void SceneManager::VistObj(SceneObject * obj,Uint32 delta)
{
	obj->Update(delta);
	for (int i = 0; i < obj->children.size();i++)
	{
		obj->children[i]->Update(delta);
	}
}

bool SceneManager::AddObject(SceneObject * parent, SceneObject * obj){
	obj->parent = parent;
	parent->children.push_back(obj);
	return true;
}

SceneObject * SceneManager::NewObject()
{
	return new SceneObject;
}

bool SceneManager::ForEach(SceneObject * obj, DealFun * fun, vector <SceneObject *> &obj_list)
{

}
