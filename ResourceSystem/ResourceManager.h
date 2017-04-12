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
		}
	};
};

class ResourceManager {
public:
	FileSystem		file;
	string			res_root;
	map<string, ResItem*> cache;
	ResourceManager();
	~ResourceManager();
	bool Init(string root);
	void Update(Uint32 delta);

	bool GetRes(string name,std::function<void (ResItem*) > cb);
	bool GetBigRes(string name, std::function<void(ResItem*) > cb);
};
#endif

//thread t(labt.fun2);
//t.detach();