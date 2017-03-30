#ifndef _SCENE_MANAGER_HPP
#define _SCENE_MANAGER_HPP
#include<Common.hpp>
#include<SceneObject.h>
#include<Camera.h>
#include<vector>
#include <RenderEngine.hpp>

class SceneManager{
public:
	int tag_id;
	SceneObject *root;
	//cameras lights_;用组件方加
public:
	SceneManager();
	~SceneManager();
	void Init();
	int GenTag();
	void Update(Uint32 delta);

	SceneObject * getRoot(){ return root; };
	SceneObject * NewObject();
	bool AddObject(SceneObject * parent, SceneObject * obj);
	
	void VistObj(SceneObject * obj, Uint32 delta);
	void DelObject(SceneObject * obj);
	
};
#endif
