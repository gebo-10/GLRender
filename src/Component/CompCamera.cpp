#include <CompCamera.h>
#include <App.h>
CompCamera::CompCamera()
{
	Vector3d pos(0.0, 0.0, 12.0);
	Vector3d target(0.0, 0.0, 0.0);
	Vector3d up(0.0, 1.0, 0.0);
	Init(pos, target, up);
}

CompCamera::~CompCamera()
{

}

void CompCamera::Init(const Vector3d& pos, const Vector3d& target, const Vector3d& up)
{
	camera.Init(pos, target, up);
	int num = 40;
	int cell = 2;
	int half = (num-1)*cell / 2;
	vector<kmVec3> vertex;
	vertex.clear();
	for (int i = 0; i < num;i++)
	{
		int x1 = -half,x2 = half;
		int y = i*cell + (-half);
		kmVec3 point1 = { x1, y, 0 };
		kmVec3 point2 = { x2, y, 0 };

		vertex.push_back(point1);
		vertex.push_back(point2);

		int y1 = -half, y2 = half;
		int x = i*cell + (-half);
		kmVec3 point3 = { x, y1, 0 };
		kmVec3 point4 = { x, y2, 0 };

		vertex.push_back(point3);
		vertex.push_back(point4);
		
	}
	Color color = {255,255,255,255};
	cmd_line.Init(vertex, color);
}

void CompCamera::Update(Uint32 delta)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.setModelViewMatrix();

	App *app = App::Instance();

	app->render.AddToCommandList(&cmd_line);
}

void CompCamera::OnMsg(int type)
{

}

void CompCamera::SetViewPort(int width, int height)
{
	win_width = width;
	win_height = height;
	glViewport(0, 0, (GLint)win_width, (GLint)win_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)win_width / (GLfloat)win_height, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	//gluLookAt(0.0, 0.0, 12.0, 0.0, 0.0, 0, 0.0, 1.0, 0.0);
}

void CompCamera::RotateX(float angle)
{
	float d = camera.getDist();
	int cnt = 100;
	float theta = angle / cnt;
	float slide_d = -2 * d*sin(theta*3.14159265 / 360);
	camera.yaw(theta / 2);
	for (; cnt != 0; --cnt)
	{
		camera.slide(slide_d, 0, 0);
		camera.yaw(theta);
	}
	camera.yaw(-theta / 2);
}

void CompCamera::RotateY(float angle)
{
	float d = camera.getDist();
	int cnt = 100;
	float theta = angle / cnt;
	float slide_d = 2 * d*sin(theta*3.14159265 / 360);
	camera.pitch(theta / 2);
	for (; cnt != 0; --cnt)
	{
		camera.slide(0, slide_d, 0);
		camera.pitch(theta);
	}
	camera.pitch(-theta / 2);
}