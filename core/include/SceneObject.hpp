#ifndef _SCENEOBJECT_HPP
#define _SCENEOBJECT_HPP
#include<Common.hpp>
#include<Component.hpp>
#include<string>

class SceneObject{
public:
	int tag;
	std::string name;

	Matrix <double,4, 4> transform;
	Vector3d position;
	Vector3d rotate;
	Vector3d scale;

	SceneObject* parent;
	std::vector<SceneObject *> children;

	std::vector<Component> comps;
public:
	SceneObject();
	~SceneObject();
	//int GetObjId();
};

#endif