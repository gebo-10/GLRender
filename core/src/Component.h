#ifndef _COMPONENT_HPP
#define _COMPONENT_HPP
#include <Base.hpp>
#include <SDL/SDL.h>
class Component{
public:
	Component();
	virtual ~Component();
public:
	virtual void Update(Uint32 delta);
	virtual void OnMsg(int type);//注释
};

#endif
