#ifndef _COMP_LIGHT_H
#define _COMP_LIGHT_H
#pragma once
#include <Component.h>
#include <Light.h>

#include <RenderCommand.h>
class CompLight :public Component
{
public:
	Light light;
	
	RcmdShadowMap rcmd;

	CompLight();
	~CompLight();
	void Init();
	void Update(Uint32 delta);

	void OnMsg(int type);

};
typedef shared_ptr<CompLight> CompLightPtr;

#endif


