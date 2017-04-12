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

	script.Init();
	log.Init(name);
	db.Init("game.db");

	resource.Init("Assets/");
	//resource.GetRes("frag.txt", [](ResItem * item) {
	//	cout.write((char *)item->buff, item->size);
	//});

	render.Init(name, width, height);
	scene.Init();

	logic.Init();
	return true;
}

bool App::Start()
{
	status = App::APP_RUN;
	MainLoop();
	return true;
}

void App::Pause()
{
	status = APP_PAUSE;
}

void App::Stop()
{
	status = APP_STOP;
}

void App::Destory(){
	LOG(INFO) << "APP Destory";
	SDL_Quit();
}


void App::MainLoop()
{
	while (1){
		if (status == APP_PAUSE)
		{
			SDL_Delay(200);//delay±£»¤ÏÂ
			continue;
		}
		if (status == APP_STOP)
		{
			Destory();
			return;
		}
		Update();
	}
}

void App::Update()
{
	Uint32 now_ticks = timer.GetTick();
	Uint32 delta = now_ticks - last_tick;
	last_tick = now_ticks;

	logic.Update(delta);
	resource.Update(delta);
	scene.Update(delta);
	render.Update(delta);
}



