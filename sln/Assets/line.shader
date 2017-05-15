{
	"param":[
	]
}
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#version 440 core

//////////////////////////////////////////////////////////////////////////
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
uniform mat4 MV;
uniform mat4 P;
layout(location = 0) in vec3 VertexPosition;

void main(){
	vec4 p2 = vec4(VertexPosition,1.0);
	gl_Position =P  *MV * p2;
}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#version 440 core
//uniform   sampler2D tex0;
out vec4 FragColor;
void main(){
	FragColor =vec4(0.5,0.5,0.6,1);
	//FragColor = texture2D(tex0,vec2(0.5,0.5));
}






