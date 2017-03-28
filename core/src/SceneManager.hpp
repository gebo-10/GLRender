#ifndef _SCENE_MANAGER_HPP
#define _SCENE_MANAGER_HPP
#include<Common.hpp>
#include<SceneObject.hpp>
#include<Camera.hpp>
#include<vector>
#include <RenderEngine.hpp>
class SceneManager{
public:
	SceneObject *root;
	RenderEngine *render;
	//cameras lights_;用组件方加
public:
	SceneManager();
	~SceneManager();
	bool Init(RenderEngine *render);
	void Update(Uint32 delta);

	SceneObject * getRoot(){ return root; };
	bool addObject(SceneObject * parent, SceneObject * obj);
	
};

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

bool SceneManager::Init(RenderEngine *render)
{
	this->render = render;
}

void SceneManager::Update(Uint32 delta)
{

}
bool SceneManager::addObject(SceneObject * parent, SceneObject * obj){
	obj->parent = parent;
	parent->children.push_back(obj);
	return true;
}


#endif
