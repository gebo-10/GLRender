#ifndef _APP_HPP
#define _APP_HPP
#pragma once
#include<Base.hpp>
#include <SceneManager.h>
#include <RenderEngine.hpp>
#include <Time.h>
#include <Logic.h>

class App
{
private:
	static App * instance;
	App();
	~App();
public:
	static App * Instance();
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

	Timer timer;

	SceneManager	scene;
	RenderEngine	render;
	Logic			logic;
	
public:

	bool Init(char * name, int width, int height);
	bool Start();
	void Stop();
	void MainLoop();
	
	void Update();
};

#endif