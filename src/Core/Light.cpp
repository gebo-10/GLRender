#include <Light.h>

Light::Light()
{
	shadow_width = 512;
	shadow_height = 512;
	vec3 pos = { 0,0,0 };
	vec3 direction = { 0,0,0 };
	Init(pos, direction);


	glGenTextures(1, &shadow_map);
	glBindTexture(GL_TEXTURE_2D, shadow_map);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadow_map, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);


	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		LOG(ERROR) << "FB error, status: " << Status;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

Light::~Light()
{

}

bool Light::Init(vec3 pos,vec3 direction)
{

	


	return true;
}

void Light::SetPosDir(vec3 pos, vec3 direction)
{
	this->pos = pos;
	this->direction = direction;

	this->target.x = pos.x + direction.x;
	this->target.y = pos.y + direction.y;
	this->target.z = pos.z + direction.z;
}

void Light::SetPosTarget(vec3 pos, vec3 target)
{
	this->pos = pos;
	this->target = target;

	this->direction.x = target.x - pos.x;
	this->direction.y = target.y - pos.y;
	this->direction.z = target.z - pos.z;
}

GPULight * Light::GetGpuLightStruct()
{
	memset(&gpu_light, 0, sizeof(gpu_light));
	gpu_light.type = type;

	gpu_light.color.x= color.r/255.0;
	gpu_light.color.y = color.g / 255.0;
	gpu_light.color.z = color.b / 255.0;
	gpu_light.color.w = color.a / 255.0;

	gpu_light.pos.x = pos.x;
	gpu_light.pos.y = pos.y;
	gpu_light.pos.z = pos.z;
	gpu_light.pos.w = 1;

	gpu_light.dir.x = direction.x;
	gpu_light.dir.y = direction.y;
	gpu_light.dir.z = direction.z;
	gpu_light.dir.w = 1;


	return &gpu_light;

}
