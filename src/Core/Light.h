#ifndef _LIGHT_H
#define _LIGHT_H
#pragma once
#include<Base.hpp>
#include <Texture.h>
#pragma pack(4)
struct GPULight{
	int index;
	int type;
	int is_shadow;
	int  xxxxx;

	mat4 VP;
	vec4 color;
	vec4 dir;
	vec4 pos;

	float min;
	float max;
	float param1;
	float param2;
};

enum LightType
{
	LT_Ambient = 1,
	LT_Directional,
	LT_Point,
	LT_Spot,
	LT_SphereArea,
	LT_TubeArea,

	LT_NumLightTypes
};
enum ShadowType
{
	ST_NONE = 0,
	ST_HARD,
	ST_SOFT,
};

class Light{
public:
	
	bool enabled;
	LightType type;

	Color color;
	vec3 pos;
	vec3 direction; //必须明确了
	vec3 target;	//必须明确了

	float range;

	GPULight gpu_light;
public:
	GLuint fbo;
	GLuint shadow_map;
	int shadow_width;
	int shadow_height;
public:
	Light();
	virtual ~Light();
	bool Init(vec3 pos, vec3 direction);
	void SetPosDir(vec3 pos, vec3 direction);
	void SetPosTarget(vec3 pos, vec3 target);

	GPULight * GetGpuLightStruct();
};
typedef shared_ptr<Light> LightPtr;
typedef weak_ptr<Light> LightWtr;

/////////////////////////////////////////////////////////////
class  AmbientLight : public Light
{
public:
	AmbientLight() {};
	virtual ~AmbientLight(){};
};

#endif