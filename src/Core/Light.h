#ifndef _LIGHT_HPP
#define _LIGHT_HPP
#pragma once
#include<Base.hpp>
#include <Texture.h>
class Light{
	enum LightType
	{
		LT_Ambient = 0,
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


protected:
	
	bool enabled;
	LightType type;
	ShadowType shadow_type;
	Color color;
	vec3 pos;
	float range;

	Texture shadow_map;
public:
	Light();
	virtual ~Light();
	bool Init();
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