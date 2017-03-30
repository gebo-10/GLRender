#ifndef _SCENE_MANAGER_HPP
#define _SCENE_MANAGER_HPP
#include<Common.hpp>
#include<SceneObject.h>
#include<Camera.h>
#include<vector>
#include <RenderEngine.hpp>
class SceneManager;
typedef bool (SceneManager::*DealFun)(void *);
class SceneManager{
public:
	SceneObject *root;
	RenderEngine *render;
	//cameras lights_;用组件方加
public:
	SceneManager();
	~SceneManager();
	void Init(RenderEngine *render);
	void Update(Uint32 delta);

	SceneObject * getRoot(){ return root; };
	SceneObject * NewObject();
	bool AddObject(SceneObject * parent, SceneObject * obj);
	
	void VistObj(SceneObject * obj, Uint32 delta);
	bool ForEach(SceneObject * obj, DealFun * fun, vector <SceneObject *> &obj_list);

};
#endif
