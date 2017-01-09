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
Model::Model()
{
	scene = NULL;
}

Model::Model(const std::string& pFile)
{	
	scene = NULL;
	Import(pFile);
}

 Model::~ Model()
{
	Release();
}

 void Model::Release()
 {
	 importer.FreeScene();
	 scene = NULL;
 }

 bool Model::Import(const std::string& pFile)
 {
	 Release();
	 // ʹ�õ���������ѡ����ģ���ļ� 
	  scene = importer.ReadFile(pFile,
		 aiProcess_CalcTangentSpace |            //�����־���Զ��������ߺ͸�����
		 aiProcess_Triangulate |                //�����־���Զ����ı�����ת��Ϊ������
		 aiProcess_JoinIdenticalVertices |    //�����־���Զ��ϲ���ͬ�Ķ���
		 aiProcess_SortByPType);                //�����־������ͬͼԪ���õ���ͬ��ģ����ȥ��ͼƬ���Ϳ����ǵ㡢ֱ�ߡ������ε�
	 //��������־���Բο�Assimp���ĵ�  
	 if (!scene)
	 {
		 //������󣬻�ȡ������Ϣ��������Ӧ�Ĵ���
		 //DoTheErrorLogging( importer.GetErrorString());     
		 return false;
	 }
	 // ������Ҫ��ȡscene�е�ģ�����ݣ��������ݵĻ�ȡ��ʽ���Բο�Assimp���ĵ�
	 //DoTheSceneProcessing( scene);   
	 std::cout << "model import succ :" << pFile << endl;
	 return true;
 }

#endif