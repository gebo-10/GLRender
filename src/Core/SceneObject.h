#ifndef _SCENEOBJECT_HPP
#define _SCENEOBJECT_HPP
#include<Common.h>
#include<Component.h>
#include<string>

class SceneObject{
public:
	enum Status
	{
		CRWEATED,
		INITED,
		ACTIVE,
		NOT_ACTIVE,
		DESTORIED,
	};
public:
	int tag;
	std::string name;

	int status;

	kmMat4 transform;
	kmVec3  position;
	kmVec3  rotate;
	kmVec3  scale;

	SceneObject* parent;
	std::vector<SceneObject *> children;

	std::vector<CompPtr> comps;
public:
	SceneObject();
	~SceneObject();

	void SetTag(int tag){ this->tag = tag; };
	void SetName(string name){ this->name = name; };

	int GetTag(){ return this->tag; };
	string GetName(){ return this->name; };

	void Update(Uint32 delta);

	void UpdateTransform();

	void AddComponent(CompPtr comp);
	CompPtr GetComponent(int tag);
	CompPtr GetComponent(string name);
	int RemoveComponent(int tag);
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};

#endif