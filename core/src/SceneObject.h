#ifndef _SCENEOBJECT_HPP
#define _SCENEOBJECT_HPP
#include<Common.hpp>
#include<Component.h>
#include<string>

class SceneObject{
public:
	int tag;
	std::string name;

	kmMat4 transform;
	Vector3d position;
	Vector3d rotate;
	Vector3d scale;

	SceneObject* parent;
	std::vector<SceneObject *> children;

	std::vector<Component *> comps;
public:
	SceneObject();
	~SceneObject();

	void SetTag(int tag){ this->tag = tag; };
	void SetName(string name){ this->name = name; };

	int SetTag(){ return this->tag; };
	string SetName(){ return this->name; };

	void Update(Uint32 delta);

	void UpdateTransform();

	void AddComponent(Component *comp);
	Component * GetComponent(int tag);
	Component * GetComponent(string name);
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};

#endif