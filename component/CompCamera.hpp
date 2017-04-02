#ifndef _COMP_CAMERA_HPP
#define _COMP_CAMERA_HPP
#pragma once
#include <Component.h>
#include <Camera.h>
#include <RenderCommand.h>
class CompCamera :public Component
{
public:
	int win_width;
	int win_height;

	RcmdLine cmd_line;

	Camera camera;
	CompCamera();
	~CompCamera();
	void Init(const Vector3d& pos, const Vector3d& target, const Vector3d& up);
	void Update(Uint32 delta);

	void OnMsg(int type);

	void RotateX(float angle);
	void RotateY(float angle);
	void SetViewPort(int width, int height);
};

#endif


