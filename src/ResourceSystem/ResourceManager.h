#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H
#pragma once
#include<Base.hpp>
#include <FileSystem.h>
//2.引用计数 资源缓存 与释放
//3.资源回调
//4 资源预取技术 能不能 改变回调 
//6 内存malloc free 优化

class ResItem {
public:
	string filename;
	void * buff;
	Uint32 size;
	ResItem() {
		buff = NULL;
		size = 0;
	};
	~ResItem() {
		size = 0;
		if (buff != NULL)
		{
			delete buff;
			buff = NULL;
			cout << "Res delete:" <<filename<< endl;
		}
	};
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
};
#endif

//thread t(labt.fun2);
//t.detach();