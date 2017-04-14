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
	void * buff;
	int data_size;
	int buff_len;
	int type;
	int gpu_memery_hint;
	
public:
	VBO();
	~VBO();
	void bind(void);
	void init(int data_size, void * buff, int type = GL_ARRAY_BUFFER, int sign = GL_STREAM_DRAW);
	
	bool UpdateDate(int data_size, void * buff);
private:

};


#endif