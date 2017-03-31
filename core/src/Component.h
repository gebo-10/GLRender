#ifndef _COMPONENT_HPP
#define _COMPONENT_HPP
#include <Base.hpp>
#include <SDL/SDL.h>
class Component{
public:
	int tag;
	string name;
	Component();
	virtual ~Component();
public:
	virtual void Update(Uint32 delta);
	virtual void OnMsg(int type);//注释

	void SetTag(int tag){ this->tag = tag; };
	void SetName(string name){ this->name = name; };

	int SetTag(){ return this->tag ; };
	string SetName(){ return this->name; };
};

#endif
