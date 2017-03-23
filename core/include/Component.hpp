#ifndef _COMPONENT_HPP
#define _COMPONENT_HPP

class Component{
public:
	Component();
	virtual ~Component();
public:
	virtual void Update();
	virtual void OnMsg(int type);

};

#endif