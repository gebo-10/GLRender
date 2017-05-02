#ifndef MESH_H
#define MESH_H
#pragma once
#include<Base.hpp>
#include<Model.h>
class Mesh{
public:
	vector<float> vertex;
	vector<int> index;
	vector<float> uv;
	vector<float> normal;
	
	Mesh();
	Mesh(aiMesh* paiMesh);
	~Mesh();
	void Init(aiMesh* paiMesh);
};


#endif