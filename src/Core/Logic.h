#ifndef _LOGIC_H
#define _LOGIC_H
#pragma once
#include<Base.hpp>
#include <ResourceManager.h>
class Logic{
public:
	Uint32 interval = 50;//50����ļ����ִ��һ�� �߼�
	Uint32 sum_delta;

	Uint32 update_count;

	ResPtr res;



	Logic();
	~Logic();
	bool Init();
	void Update(Uint32 delta);
	void Do(Uint32 delta);
};
#endif