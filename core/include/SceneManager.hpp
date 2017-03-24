#ifndef _SCENE_MANAGER_HPP
#define _SCENE_MANAGER_HPP
#include<Common.hpp>
#include<SceneObject.hpp>
#include<Camera.hpp>
#include<vector>
class SceneManager{
public:
	SceneObject *root;
	//std::vector<Camera> cameras;用组件方加
	//std::vector<LightSourcePtr> lights_;
public:
	SceneManager();
	~SceneManager();
	//int GetObjId();
	SceneObject * getRoot(){ return root; };
	bool addObject(SceneObject * parent, SceneObject * obj);
};

bool SceneManager::addObject(SceneObject * parent, SceneObject * obj){
	obj->parent = parent;
	parent->children.push_back(obj);
	return true;
}
#endif
