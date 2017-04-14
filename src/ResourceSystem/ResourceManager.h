#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H
#pragma once
#include<Base.hpp>
#include <FileSystem.h>
//2.���ü��� ��Դ���� ���ͷ�
//3.��Դ�ص�
//4 ��ԴԤȡ���� �ܲ��� �ı�ص� 
//6 �ڴ�malloc free �Ż�
enum ResType
{
	NORMAL,
	SHADER,
};
class ResItem {
public:
	string filename;
	void * buff;
	Uint32 size;
	ResItem() {
		buff = NULL;
		size = 0;
	};
	virtual ~ResItem() {
		size = 0;
		if (buff != NULL)
		{
			delete buff;
			buff = NULL;
			cout << "Res delete:" <<filename<< endl;
		}
	};
	virtual bool Init() { return true; };
};
typedef  shared_ptr<ResItem> ResPtr;

class ResourceManager {
public:
	FileSystem		file;
	string			res_root;
	map<string, weak_ptr<ResItem> > cache;
	ResourceManager();
	~ResourceManager();
	bool Init(string root);
	void Update(Uint32 delta);

	bool Cache(string filename, ResPtr res);
	bool DeCache(string filename) ;

	bool GetRes(string name,std::function<void (ResPtr) > cb);
	bool GetBigRes(string name, std::function<void(ResPtr) > cb);

	bool SaveRes(string name, ResPtr res);


public:
	int default_shader;
	int GetDefaultShader() { return default_shader; };

};
#endif

//thread t(labt.fun2);
//t.detach();