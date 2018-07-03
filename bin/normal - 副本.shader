{
	"param":[
		["testint","show in editor","int",1],
		["testfloat","show in editor","float",2.0],
		["testcolor","show in editor","color",[0.1,0.5,1,1]],
		["tex1","show in editor","texture","Texure/pure.png"]
	]	
}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#version 440 core

layout(shared , column_major) uniform;
layout (std140) uniform Global{  
    float time;  
    vec4 color;  
}G;


uniform float a; 
uniform mat4 MV;
uniform mat4 P;
uniform mat4 MVP;
layout(location = 0) in vec3 VertexPosition;

layout(location = 1) in vec2 vertTexCoord;

layout(location = 2) in vec3 Normal_local;

flat out  float b; 

 out  vec3 normal; 

out vec2 fragTexCoord;
vec4 p2; 
void main(){
	b=a;
	normal = (MV * vec4(Normal_local, 0.0)).xyz;  
	fragTexCoord=vertTexCoord;
	p2 = vec4(VertexPosition,1.0);
	gl_Position =MVP * p2;
	
	
}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#version 440 core

layout(shared , column_major) uniform;
layout (std140) uniform Global{  
    float time;  
    vec4 color;  
}G;

 uniform   sampler2D tex1;
 uniform   sampler2D tex0;
 uniform   vec3 light_Color;  
 uniform   float AmbientIntensity;  
 uniform   float DiffuseIntensity;
 uniform   vec3 Direction;  

in vec2 fragTexCoord;
flat in  float b;

in  vec3 normal;

out vec4 FragColor; 

void main(){
	FragColor =vec4(0.5,0.5,1,1);
	//FragColor =normal;
	//FragColor = texture2D(tex0,fragTexCoord.st);


	float DiffuseFactor = dot(normalize(normal),normalize(Direction) );

	vec4 DiffuseColor;
    if (DiffuseFactor > 0) {
        DiffuseColor = vec4(light_Color, 1.0f) * DiffuseIntensity * DiffuseFactor;
    }
    else {
        DiffuseColor = vec4(0, 0, 0, 0);
    }

	vec4 AmbientColor=vec4(light_Color, 1.0f) *AmbientIntensity;
	FragColor = texture2D(tex1,fragTexCoord.st)* (AmbientColor + DiffuseColor);

	//FragColor =vec4(0.5,0.1,1,1)* (AmbientColor + DiffuseColor);
	FragColor=G.color;
}






