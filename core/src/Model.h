#ifndef MODEL_H
#define MODEL_H
#pragma once

#include <Base.hpp>
#include <assimp/Importer.hpp>      // �������ڸ�ͷ�ļ��ж���
#include <assimp/scene.h>           // ��ȡ����ģ�����ݶ�����scene��
#include <assimp/postprocess.h>     // ��ͷ�ļ��а�������ı�־λ����
#pragma comment(lib,"assimp-vc120-mt.lib") 
class  Model
{
public:
	Model();
	Model(const std::string& pFile);
	~ Model();
	void Release();
	bool Import(const std::string& pFile);

	// ����һ�������� 
	Assimp::Importer importer;
	const aiScene* scene;
private:
	
};

#endif