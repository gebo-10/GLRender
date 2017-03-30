#include<SceneManager.h>
SceneManager::SceneManager()
{
	tag_id = 0;
}

SceneManager::~SceneManager()
{

}

void SceneManager::Init()
{
	root = new SceneObject;
}

int SceneManager::GenTag()
{
	return ++tag_id;
}

void SceneManager::Update(Uint32 delta)
{
	VistObj(root,delta);
}

SceneObject * SceneManager::NewObject()
{
	return new SceneObject;
}

void SceneManager::VistObj(SceneObject * obj,Uint32 delta)
{
	obj->Update(delta);
	for (int i = 0; i < obj->children.size();i++)
	{
		VistObj(obj->children[i], delta);
	}
}

bool SceneManager::AddObject(SceneObject * parent, SceneObject * obj){
	obj->parent = parent;
	parent->children.push_back(obj);
	return true;
}

void SceneManager::DelObject(SceneObject * obj){
	for (int i = 0; i < obj->children.size(); i++)
	{
		DelObject(obj);
	}
	delete obj;
}

SceneObject * SceneManager::FindObject(int tag){

}
