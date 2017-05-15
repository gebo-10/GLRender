#ifndef _APP_H
#define _APP_H
#pragma once
#include<Base.hpp>
#include <SceneManager.h>
#include <RenderEngine.h>
#include <Time.h>
#include <Logic.h>
#include <ScriptEngine.h>
#include <Log.h>
#include <DB.h>
#include <ResourceManager.h>


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

	ScriptEngine	script;
	SceneManager	scene;
	RenderEngine	render;
	ResourceManager resource;
	Timer			timer;
	Logic			logic;
	Log				log;
	DB				db;


public:

	bool Init(char * name, int width, int height);
	bool Start();
	void Pause();
	void Stop();

	void Destory();
	void Update();
	void MainLoop();
};

#endif