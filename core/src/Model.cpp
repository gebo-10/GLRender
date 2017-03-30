#include<Model.h>
Model::Model()
{
	scene = NULL;
}

Model::Model(const std::string& pFile)
{
	scene = NULL;
	Import(pFile);
}

Model::~Model()
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
	// 使用导入器导入选定的模型文件 
	scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |            //后处理标志，自动计算切线和副法线
		aiProcess_Triangulate |                //后处理标志，自动将四边形面转换为三角面
		aiProcess_JoinIdenticalVertices |    //后处理标志，自动合并相同的顶点
		aiProcess_SortByPType);                //后处理标志，将不同图元放置到不同的模型中去，图片类型可能是点、直线、三角形等
	//更多后处理标志可以参考Assimp的文档  
	if (!scene)
	{
		//导入错误，获取错误信息并进行相应的处理
		//DoTheErrorLogging( importer.GetErrorString());     
		return false;
	}
	// 根据需要获取scene中的模型数据，各种数据的获取方式可以参考Assimp的文档
	//DoTheSceneProcessing( scene);   
	std::cout << "model import succ :" << pFile << endl;
	return true;
}