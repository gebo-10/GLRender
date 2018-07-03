{
	"param":[
	]
}
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#version 440 core

uniform mat4 MV;
uniform mat4 P;
uniform mat4 MVP;

layout(shared , column_major) uniform;
layout (std140) uniform Global{  
    float time;  
    vec4 color;  
}G;


layout(location = 0) in vec3 VertexPosition;

void main(){
	gl_Position =MVP *vec4(VertexPosition,1.0);
}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#version 440 core

out vec4 FragColor;
void main(){
	FragColor =vec4(1.0);
}
