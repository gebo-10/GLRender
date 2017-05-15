#include <CompCamera.h>
#include <CompMeshRender.hpp>
#include <CompLight.h>
#include <Logic.h>
#include <App.h>
#include <math.h>
#include <Font.h>
Logic::Logic()
{
	update_count = 0;
}

Logic::~Logic()
{

}

bool Logic::Init()
{
	App *app = App::Instance();

	app->scene.getRoot()->position.x = 0;

	SceneObject *obj = new SceneObject();
	obj->position.x = 0;
	obj->tag = 2;
	CompCameraPtr camera = make_shared<CompCamera>() ;
	camera->SetName("main_camera");
	camera->SetViewPort(512, 512);
	camera->camera.slide(0, 0, 30);
	obj->AddComponent(camera);

	CompMeshRenderPtr comp_mesh = make_shared<CompMeshRender>(); 
	comp_mesh->SetName("box_render");
	comp_mesh->SetTag(2);
	comp_mesh->Init("Assets/Model/box.fbx","first.mtl");
	obj->AddComponent(comp_mesh);
	obj->scale.x = 0.20;
	obj->scale.y = 0.20;
	obj->scale.z = 0.20;
	obj->position.z = 3;
	obj->rotate.x = 45;
	app->scene.AddObject(app->scene.getRoot(), obj);

	obj = new SceneObject();
	CompMeshRenderPtr comp_mesh2 = make_shared<CompMeshRender>();
	comp_mesh2->SetTag(3);
	comp_mesh2->Init("Assets/Model/plane.fbx", "second.mtl");


	obj->AddComponent(comp_mesh2);
	obj->scale.x = 10;
	obj->scale.y = 10;
	obj->scale.z = 10;
	obj->position.z = 0;
	obj->rotate.x = 0;
	app->scene.AddObject(app->scene.getRoot(), obj);

	obj = new SceneObject();
	
	obj->SetTag(121);


	CompLightPtr comp_light = make_shared<CompLight>();
	comp_light->SetName("light");
	comp_light->SetTag(1);
	comp_light->Init();
	comp_light->light.SetPosTarget(vec3({ -10,0,10 }), vec3({ 0,0,0 }));
	Color c;
	c.r = 100;
	c.g = 200;
	c.b = 30;
	c.a = 255;
	comp_light->light.color = c;
	comp_light->light.type = LT_Directional;

	obj->AddComponent(comp_light);


	CompLightPtr comp_light2 = make_shared<CompLight>();
	comp_light2->SetName("light2");
	comp_light2->SetTag(2);
	comp_light2->Init();
	comp_light2->light.SetPosTarget(vec3({ -10,0,10 }), vec3({ 0,0,0 }));
	Color c2;
	c2.r = 50;
	c2.g = 0;
	c2.b = 0;
	c2.a = 255;
	comp_light2->light.color = c2;
	comp_light2->light.type = LT_Ambient;

	obj->AddComponent(comp_light2);



	obj->scale.x =1;
	obj->scale.y = 1;
	obj->scale.z = 1;
	obj->position.z = 1;
	obj->position.x =0;
	obj->rotate.x = 0;
	app->scene.AddObject(app->scene.getRoot(), obj);


	for (int i = 0; i < 0;i++)
	{

		obj = new SceneObject();
		obj->tag = 100+i;
		obj->position.x = 10 * i;
		obj->position.y = 15 * i;
		obj->rotate.z = 45*i ;
		obj->rotate.y = 45 * i;

		obj->scale.x = 0.1 * i;
		obj->scale.z = 0.1 * i;
		obj->scale.y = 0.1 * i;

		comp_mesh = make_shared<CompMeshRender>();
		comp_mesh->SetTag(1);
		comp_mesh->Init("box.fbx","second.mtl");

		obj->AddComponent(comp_mesh);
		app->scene.AddObject(app->scene.getRoot(), obj);
	}
	
	return true;
}

void Logic::Update(Uint32 delta)
{
	sum_delta += delta;
	if (sum_delta >= interval)
	{
		Do(sum_delta);
		App::Instance()->script.Update();
		sum_delta = 0;
	}
}

void Logic::Do(Uint32 delta)
{
	App *app = App::Instance();
	SceneObject * obj=app->scene.FindObject(2);
	CompCameraPtr  camera = static_pointer_cast<CompCamera>(  obj->GetComponent("main_camera") );
	static Vector2i lastPos;

	int dx, dy;
	SDL_Event e;
	int times = 3;//??? Õ¦Õû
	while (SDL_PollEvent(&e) && times >0){
		times--;
		switch (e.type){
		case SDL_QUIT:
			app->Stop();
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE: app->Stop(); break;
			case SDLK_x: 
				for (int i = 0; i < 10; i++)
				{
					SceneObject * obj = app->scene.FindObject(100 + i);
					obj->rotate.x++;
				}
			break;
			case SDLK_y:
				for (int i = 0; i < 10; i++)
				{
					SceneObject * obj = app->scene.FindObject(100 + i);
					obj->rotate.x--;
				}
			break;
			case SDLK_a:
				app->resource.GetRes("frag.txt", [this](ResPtr res) {
					this->res = res;
					cout.write((char *)res->buff, res->size);
				});
			break;
			case SDLK_b:
				this->res = nullptr;
				break;
			case SDLK_c:
				obj->RemoveComponent(2);
				break;

			case SDLK_d:
			{
					SceneObject * obj = app->scene.FindObject(121);
					CompLightPtr  light_cnmp = static_pointer_cast<CompLight>(obj->GetComponent("light"));
					
					//double tmp = (double)update_count;
					double deg = (double)(update_count % 360) / 360 * 3.1415926*2;
					
					
					light_cnmp->light.SetPosTarget(vec3({ 50* (float) cos(deg),50 * (float)sin(deg),20 }), vec3({ 0,0,0 }));
				break;
			}
			case SDLK_e:
			{
				Font font;
				font.Init();
				font.SetFont("xxx");
				font.SetFontSize(36);
				TexturePtr ptr = font.GetStrTexture("xx");
				ShaderParamValue val;
				val.ptr = ptr;

				SceneObject *obj = app->scene.FindObject(2);
				CompMeshRenderPtr comp22 = static_pointer_cast<CompMeshRender>(obj->GetComponent("box_render"));
				comp22->meshs[0].material->param[0].value = val;
				break;
			}
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
	while (SDL_PollEvent(&e)){}


	update_count++;
	//SDL_PumpEvents();
	//arg = (arg + 0.1);
	//int tmpint = (int)arg;
	//arg = arg - tmpint;
	//glUniform1f(loc, arg); 

}
