#include <CompLight.h>
#include <App.h>
CompLight::CompLight()
{

}

CompLight::~CompLight()
{

}

void CompLight::Init()
{
	rcmd.Init(&light);
}


void CompLight::Update(Uint32 delta)
{
	App::Instance()->render.AddToCommandList(&rcmd);
}

void CompLight::OnMsg(int type)
{

}
