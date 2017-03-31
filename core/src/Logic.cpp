#include <CompCamera.hpp>
#include <CompMeshRender.hpp>
#include <Logic.h>
#include <App.h>
Logic::Logic()
{
}

Logic::~Logic()
{

}

bool Logic::Init()
{
	App *app = App::Instance();
	SceneObject *obj = new SceneObject();
	obj->tag = 110;
	Component * comp = new CompCamera();
	comp->SetName("main_camera");
	obj->AddComponent(comp);

	CompMeshRender *comp_mesh = new CompMeshRender();
	comp_mesh->Init("box.fbx");
	obj->AddComponent(comp_mesh);
	app->scene.AddObject(app->scene.getRoot(), obj);

	return true;
}

void Logic::Update(Uint32 delta)
{
	sum_delta += delta;
	if (sum_delta >= interval)
	{
		Do(sum_delta);
		sum_delta = 0;
	}
}

void Logic::Do(Uint32 delta)
{
	App *app = App::Instance();
	SceneObject * obj=app->scene.FindObject(110);
	CompCamera * camera = (CompCamera *)obj->GetComponent("main_camera");
	int x = 0, y = 0;
	static Vector2i lastPos;
	int dx, dy;
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		cout << e.type << endl;
		switch (e.type){
		case SDL_QUIT:
			app->Stop();
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE: app->Stop(); break;
			case SDLK_x: x = x + 1; break;
			case SDLK_y: y = y - 1; break;

			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			lastPos << e.button.x, e.button.y;
			if (e.button.button == SDL_BUTTON_LEFT){

			}
			if (e.button.button == SDL_BUTTON_RIGHT){

			}
			if (e.button.button == SDL_BUTTON_MIDDLE){

			}
			break;
		case SDL_MOUSEMOTION:
			dx = e.button.x - lastPos.x();
			dy = e.button.y - lastPos.y();

			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				camera->RotateX(dx);
				camera->RotateY(dy);
				break;
			case SDL_BUTTON_RIGHT:
				camera->camera.roll(dx);
				break;
			case SDL_BUTTON_MIDDLE:
				camera->camera.slide(-dx, dy, 0);
				break;
			}

			lastPos << e.button.x, e.button.y;
			break;
		case SDL_MOUSEWHEEL:

			camera->camera.slide(0, 0, -e.wheel.y);
			break;
		}
	}


	//arg = (arg + 0.1);
	//int tmpint = (int)arg;
	//arg = arg - tmpint;
	//glUniform1f(loc, arg);

}
