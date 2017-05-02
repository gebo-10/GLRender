#version 440 core

#version 330
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;
uniform mat4 gWVP;
out vec2 TexCoordOut;
void main()
{
    gl_Position = gWVP * vec4(Position, 1.0);
    TexCoordOut = TexCoord;
}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#version 440 core
//uniform   sampler2D tex0;
out vec4 FragColor;
void main(){
	FragColor =vec4(1.0,0);
	//FragColor = texture2D(tex0,vec2(0.5,0.5));
}






