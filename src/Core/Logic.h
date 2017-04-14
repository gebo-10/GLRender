#ifndef _LOGIC_HPP
#define _LOGIC_HPP
#pragma once
#include<Base.hpp>
#include <ResourceManager.h>
class Logic{
public:
	Uint32 interval = 50;//50毫秒的间隔才执行一次 逻辑
	Uint32 sum_delta;

	ResPtr res;

	Logic();
	~Logic();
	bool Init();
	void Update(Uint32 delta);
	void Do(Uint32 delta);
};
#endif