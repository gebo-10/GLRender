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


#endif