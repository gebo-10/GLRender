
#include <Camera.h>

Camera::Camera()
{
	
}

Camera::Camera(const Vector3d pos, const Vector3d target, const Vector3d up)
{
	Init(pos, target, up);
}

void Camera::Init(const vec3 pos, const vec3 target)
{
	Vector3d Epos(pos.x, pos.y, pos.z);
	Vector3d Etarget(target.x, target.y, target.z);
	Vector3d Eup(0.0, 1.0, 0.0);
	Init(Epos, Etarget, Eup);
}

void Camera::Init(const Vector3d pos, const Vector3d target, const Vector3d up)
{
	this->pos = pos;
	this->target = target;
	this->up = up;
	n = Vector3d(pos.x() - target.x(), pos.y() - target.y(), pos.z() - target.z());
	u = Vector3d(up.cross(n).x(), up.cross(n).y(), up.cross(n).z());
	v = Vector3d(n.cross(u).x(), n.cross(u).y(), n.cross(u).z());


	n.normalize();
	u.normalize();
	v.normalize();

	SetModelViewMatrix();
}

void Camera::SetViewPort(int width, int height)
{
	int win_width = width;
	int win_height = height;
	glViewport(0, 0, (GLint)win_width, (GLint)win_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)win_width / (GLfloat)win_height, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::SetModelViewMatrix()
{
	double m[16];
	m[0] = u.x(); m[4] = u.y(); m[8] = u.z(); m[12] = -pos.dot(u);
	m[1] = v.x(); m[5] = v.y(); m[9] = v.z(); m[13] = -pos.dot(v);
	m[2] = n.x(); m[6] = n.y(); m[10] = n.z(); m[14] = -pos.dot(n);
	m[3] = 0;  m[7] = 0;  m[11] = 0;  m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(m);     //用M矩阵替换原视点矩阵
}

void  Camera::setShape(float viewAngle, float aspect, float Near, float Far)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                                   //设置当前矩阵模式为投影矩阵并归一化
	gluPerspective(viewAngle, aspect, Near, Far);        //对投影矩阵进行透视变换
}

void Camera::slide(float du, float dv, float dn)
{
	//std::cout<<"u.x:"<<u.x()<<std::endl;
	pos(0) = pos(0) + du*u.x() + dv*v.x() + dn*n.x();
	pos(1) = pos(1) + du*u.y() + dv*v.y() + dn*n.y();
	pos(2) = pos(2) + du*u.z() + dv*v.z() + dn*n.z();
	target(0) = target(0) + du*u.x() + dv*v.x() + dn*n.x();
	target(1) = target(0) + du*u.y() + dv*v.y() + dn*n.y();
	target(2) = target(0) + du*u.z() + dv*v.z() + dn*n.z();
	SetModelViewMatrix();
}

void Camera::roll(float angle)
{
	float cs = cos(angle*3.14159265 / 180);
	float sn = sin(angle*3.14159265 / 180);
	Vector3d t(u);
	Vector3d s(v);
	u.x() = cs*t.x() - sn*s.x();
	u.y() = cs*t.y() - sn*s.y();
	u.z() = cs*t.z() - sn*s.z();

	v.x() = sn*t.x() + cs*s.x();
	v.y() = sn*t.y() + cs*s.y();
	v.z() = sn*t.z() + cs*s.z();

	SetModelViewMatrix();          //每次计算完坐标轴变化后调用此函数更新视点矩阵
}

void Camera::pitch(float angle)
{
	float cs = cos(angle*3.14159265 / 180);
	float sn = sin(angle*3.14159265 / 180);
	Vector3d t(v);
	Vector3d s(n);

	v.x() = cs*t.x() - sn*s.x();
	v.y() = cs*t.y() - sn*s.y();
	v.z() = cs*t.z() - sn*s.z();

	n.x() = sn*t.x() + cs*s.x();
	n.y() = sn*t.y() + cs*s.y();
	n.z() = sn*t.z() + cs*s.z();


	SetModelViewMatrix();
}

void Camera::yaw(float angle)
{
	float cs = cos(angle*3.14159265 / 180);
	float sn = sin(angle*3.14159265 / 180);
	Vector3d t(n);
	Vector3d s(u);

	n.x() = cs*t.x() - sn*s.x();
	n.y() = cs*t.y() - sn*s.y();
	n.z() = cs*t.z() - sn*s.z();

	u.x() = sn*t.x() + cs*s.x();
	u.y() = sn*t.y() + cs*s.y();
	u.z() = sn*t.z() + cs*s.z();

	SetModelViewMatrix();
}

float  Camera::getDist()
{
	float dist = pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2);
	return pow(dist, 0.5);
}


