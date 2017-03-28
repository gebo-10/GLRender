#ifndef VBO_H
#define VBO_H
#include<GL/glew.h>
using namespace std;
//GL_ARRAY_BUFFER
//GL_ELEMENT_ARRAY_BUFFER
class VBO
{
public:
	GLuint id;
	char * buff;
	int data_size;
	int buff_len;
	int type;
	
public:
	VBO();
	void bind(void);
	void init( int data_size, void * buff,int type, int sign);
	~VBO();

private:

};
VBO::VBO() :id(0),type(GL_ARRAY_BUFFER), buff_len(0), data_size(0), buff(NULL){}

//data_size Îª×Ö½ÚÊý
void VBO::init(int data_size, void * buff, int type = GL_ARRAY_BUFFER, int sign = GL_STATIC_DRAW){
	glGenBuffers(1, &id);
	glBindBuffer(type, id);
	glBufferData(type, data_size, buff, sign); 
	//glBindBuffer(type, 0);
}
void VBO::bind(void){
	glBindBuffer(type, id); 
}
VBO::~VBO(){}


#endif