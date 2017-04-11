#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H
#pragma once
#include<Base.hpp>
//1.文件系统的兼容 http win linux anroid ios
//2.引用计数 资源缓存 与释放
//3.资源回调
//4 资源预取技术 能不能 改变回调 
//5 大文件 内存映射技术

class ResItem {
public:
	void * content;
	Uint32 size;
	ResItem() {
		content = NULL;
		size = 0;
	};
	~ResItem() {};
};

class ResCallBack {
public:
	ResItem *res;
	ResCallBack() {};
	~ResCallBack() {};
	virtual void CallBack() {};
};

class ResourceManager {
public:
	map<string, ResItem> cache;
	ResourceManager();
	~ResourceManager();
	bool Init(string root);
	void Update(Uint32 delta);

	bool GetRes(string name,ResCallBack * cb);
	bool GetBigRes(string name, ResCallBack * cb);
};
#endif