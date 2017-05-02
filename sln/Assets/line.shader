{
	"param":[
	]
}
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#version 440 core

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






