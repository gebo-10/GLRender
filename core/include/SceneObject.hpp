#ifndef _SCENEOBJECT_HPP
#define _SCENEOBJECT_HPP
#include<Common.hpp>
class SceneObject{
public:
	Vector3f position;
	Vector3f rotate;
	Vector3f scale;
	
public:
	SceneObject();
	~SceneObject();
	//int GetObjId();
};

#endif