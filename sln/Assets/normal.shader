{
	"param":[
		["font_texture","ShowInEditor","texture","Texure/pure.png"]
	]	
}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//////////////////////////////////////////////////////////////////////////
#version 440 core

layout(shared , column_major) uniform;
layout (std140) uniform Global{  
	float time;  
	vec4 color;  
}G;

//////////////////////////////////////////////////////////////////////////
int LIGHT_NUM =10;
struct LightStruct{
	int  index;
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

layout (std140)uniform Light{
	LightStruct lights[10]; //与c++ 对应起来最好了
};

uniform sampler2DShadow shadow_map[10];
out vec4 shadow_coord[10];
////////////////////////////////////////////////////////////////////////////

uniform mat4 P;
uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 NormalLocal;


out vec3 NormalGlobal; 
out vec2 FlatTextureCoord;


void main(){
	NormalGlobal = (M * vec4(NormalLocal, 0.0)).xyz;  
	FlatTextureCoord=TextureCoord;

	vec4 local_coord=vec4(VertexPosition,1.0);
	vec4 world_coord = M*local_coord;

	for(int i=0;i<LIGHT_NUM;i++)
	{
		shadow_coord[i]=lights[i].VP* world_coord;
	}
	
	gl_Position =MVP * local_coord;
	
}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//////////////////////////////////////////////////////////////////////////
#version 440 core

layout(shared , column_major) uniform;
layout (std140) uniform Global{  
	float time;  
	vec4 color;  
}G;

//////////////////////////////////////////////////////////////////////////
int LIGHT_NUM =10;
struct LightStruct{
	int  index;
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

layout (std140)uniform Light{
	LightStruct lights[10]; //与c++ 对应起来最好了
};

uniform sampler2DShadow shadow_map[10];
in vec4 shadow_coord[10];
////////////////////////////////////////////////////////////////////////////
in vec2 FlatTextureCoord;
in vec3 NormalGlobal;


uniform sampler2D font_texture;
 
uniform   vec3 light_Color;  
uniform   float AmbientIntensity;  
uniform   float DiffuseIntensity;
  
////////////////////////////////////////////////////////////////////////////
out vec4 FragColor; 


//float CalcShadowFactor(vec4 LightSpacePos)
//{
//    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;
//    vec2 UVCoords;
//    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
//    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
//    float z = 0.5 * ProjCoords.z + 0.5;
//    float Depth = texture(shadow_map[0], UVCoords).x;
//    if (Depth < z )
//        return 0.2;
//    else
//        return 1.0;
//}

float CalcShadowFactor2(vec4 LightSpacePos)
{
    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;
    vec2 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    float z = 0.5 * ProjCoords.z + 0.5;
    float xOffset = 1.0/512;
    float yOffset = 1.0/512;
    float Factor = 0.0;
    for (int y = -2 ; y <= 2 ; y++) {
        for (int x = -2 ; x <= 2 ; x++) {
            vec2 Offsets = vec2(x * xOffset, y * yOffset);
            vec3 UVC = vec3(UVCoords + Offsets, z );
            Factor += texture(shadow_map[0], UVC);
        }
    }
    return (0.5 + (Factor / 50.0));
} 

//vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal, float ShadowFactor)
//{
//    ...
//    return (AmbientColor + ShadowFactor * (DiffuseColor + SpecularColor));
//} 
//
//vec4 CalcDirectionalLight(vec3 Normal)
//{
//    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, Normal, 1.0);
//} 

//vec4 CalcPointLight(struct PointLight l, vec3 Normal, vec4 LightSpacePos)
//{
//    vec3 LightDirection = WorldPos0 - l.Position;
//    float Distance = length(LightDirection);
//    LightDirection = normalize(LightDirection);
//    float ShadowFactor = CalcShadowFactor(LightSpacePos);
//    vec4 Color = CalcLightInternal(l.Base, LightDirection, Normal, ShadowFactor);
//    float Attenuation = l.Atten.Constant +
//        l.Atten.Linear * Distance +
//        l.Atten.Exp * Distance * Distance;
//    return Color / Attenuation;
//} 

//vec4 CalcSpotLight(struct SpotLight l, vec3 Normal, vec4 LightSpacePos)
//{
//    vec3 LightToPixel = normalize(WorldPos0 - l.Base.Position);
//    float SpotFactor = dot(LightToPixel, l.Direction);
//
//    if (SpotFactor > l.Cutoff) {
//        vec4 Color = CalcPointLight(l.Base, Normal, LightSpacePos);
//        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - l.Cutoff));
//    }
//    else {
//        return vec4(0,0,0,0);
//    }
//}  

//////////////////////////////////////////////////////////////////////////////////
vec4 CalcDirectionLight(vec4 color,vec3 dir,vec3 normal,float diffuse_intensity)
{
	
	float DiffuseFactor = dot(normalize(normal),normalize(dir) );

	vec4 DiffuseColor;
    if (DiffuseFactor > 0) {
        DiffuseColor =color * diffuse_intensity * DiffuseFactor;
    }
    else {
        DiffuseColor = vec4(0,0,0,0);
    }
    return DiffuseColor;
}

void main(){
	
	vec4 total_color=vec4(0,0,0,1);
	for(int i=0;i< LIGHT_NUM; i++)
	{
		vec4 color_tmp=vec4(0,0,0,1);
		switch(lights[i].type)
		{
			case 1:
				color_tmp=lights[i].color;//vec4(0,1,0,1);//
				break;
			case 2:
				//CalcShadowFactor2(vec4 LightSpacePos)
				color_tmp=CalcDirectionLight(lights[i].color, lights[i].dir.xyz, NormalGlobal, 0.5);
				break;
		}
		total_color+=color_tmp;
	}

	FragColor=texture2D(font_texture,FlatTextureCoord.st) *total_color;
	FragColor=total_color;


    //return (AmbientColor + ShadowFactor * (DiffuseColor + SpecularColor));
}






