#ifndef MODEL_H
#define MODEL_H
#pragma once

#include <Base.hpp>
#include <assimp/Importer.hpp>      // 导入器在该头文件中定义
#include <assimp/scene.h>           // 读取到的模型数据都放在scene中
#include <assimp/postprocess.h>     // 该头文件中包含后处理的标志位定义
#pragma comment(lib,"assimp-vc120-mt.lib") 
class  Model
{
public:
	Model();
	Model(const std::string& pFile);
	~ Model();
	void Release();
	bool Import(const std::string& pFile);

	// 定义一个导入器 
	Assimp::Importer importer;
	const aiScene* scene;
private:
	
};

#endif