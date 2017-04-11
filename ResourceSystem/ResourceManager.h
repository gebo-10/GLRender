#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H
#pragma once
#include<Base.hpp>
//1.�ļ�ϵͳ�ļ��� http win linux anroid ios
//2.���ü��� ��Դ���� ���ͷ�
//3.��Դ�ص�
//4 ��ԴԤȡ���� �ܲ��� �ı�ص� 
//5 ���ļ� �ڴ�ӳ�似��

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