#ifndef CAMERA_H
#define CAMERA_H
#pragma once
#include<Common.h>
#include <Base.hpp>
class Camera
{
public:
	Camera();
	Camera(const Vector3d pos, const Vector3d target, const Vector3d up);
	void Init(const Vector3d pos, const Vector3d target, const Vector3d up);
	void Init(const vec3 pos, const vec3 target);
	void SetViewPort(int width, int height);
	void SetModelViewMatrix();
	void setShape(float viewAngle, float aspect, float Near, float Far);
	void slide(float du, float dv, float dn);
	void roll(float angle);
	void yaw(float angle);
	void pitch(float angle);
	float getDist();

private:
	Vector3d pos;
	Vector3d target;
	Vector3d up;
	Vector3d u, v, n;

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

#endif
