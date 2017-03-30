#include <App.h>

App *App::instance = NULL;
App::App()
{
	status = App::APP_PAUSE;
}

App::~App()
{

}
App * App::Instance()
{
	if (instance == NULL)
		instance = new App();
	return instance;
}

bool App::Init(char * name, int width, int height)
{
	strcpy(this->name, name);
	this->width = width;
	this->height = height;

	render.Init(name, width, height);
	scene.Init(&render);

	logic.Init();
	return true;
}

bool App::Start()
{
	status = App::APP_RUN;
	MainLoop();
	return true;
}

void App::Stop()
{
	SDL_Quit();
}

void App::MainLoop()
{
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

void App::Update()
{
	Uint32 now_ticks = timer.GetTick();
	Uint32 delta = now_ticks - last_tick;
	last_tick = now_ticks;

	logic.Update(delta);
	scene.Update(delta);
	render.Update(delta);
}



