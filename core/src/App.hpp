#ifndef _APP_HPP
#define _APP_HPP
#pragma once
#include<Base.hpp>
#include <SceneManager.hpp>
#include <RenderEngine.hpp>
#include <time.hpp>
class App
{
public:
	enum AppStatus
	{
		APP_STOP = 0,
		APP_RUN,
		APP_PAUSE,
	};
public:
	char name[100];
	int width;
	int height;

	int status;
	Uint32 last_tick;


	SceneManager scene;
	RenderEngine render;
	Timer timer;
public:
	App();
	~App();
	bool Init(char * name, int width, int height);
	bool Start();
	void MainLoop();
	
	void Update();
};

App::App()
{
	status = App::APP_PAUSE;
}

App::~App()
{

}

void App::MainLoop()
{
	SDL_Event e;
	while (1){
		if (status == APP_PAUSE)
		{
			SDL_Delay(200);//delay
			continue;
		}
		if (status == APP_STOP)
		{
			return;
		}
		Update();

		SDL_Delay(100);//±£»¤ÏÂ
	}
}

bool App::Init(char * name, int width, int height)
{
	strcpy(this->name, name);
	this->width = width;
	this->height = height;
	
	render.Start(name,width,height);
	scene.Init(&render);

}

bool App::Start()
{
	status = App::APP_RUN;
	MainLoop();
}

void App::Update()
{
	Uint32 now_ticks=timer.GetTick();
	Uint32 delta=now_ticks-last_tick;
	last_tick = now_ticks;

	scene.Update(delta);
	render.Update(delta);
}

#endif