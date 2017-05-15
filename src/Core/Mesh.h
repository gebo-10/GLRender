#ifndef MESH_H
#define MESH_H
#pragma once
#include<Base.hpp>
#include<Model.h>
class Mesh{
public:
	vector<float> vertex;
	vector<float> uv;
	vector<float> normal;

	vector<int> index;
	
	Mesh();
	Mesh(aiMesh* paiMesh);
	~Mesh();
	void Init(aiMesh* paiMesh);
};

typedef std::shared_ptr<Mesh> MeshPtr;

#endif