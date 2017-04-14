#ifndef VAO_H
#define VAO_H
#include<GL/glew.h>
#include<vector>
#include<VBO.h>
using namespace std;
class VAO
{
public:
	GLuint id;
	vector<VBO> vbos;
public:
	VAO();
	~VAO();
	void Init(void);
	void Bind(void);
	void UnBind(void);
	int NewVBO(int data_size, void * buff, int type = GL_ARRAY_BUFFER, int sign = GL_STREAM_DRAW);
	int NewEBO(int data_size, void * buff, int type = GL_ELEMENT_ARRAY_BUFFER, int sign = GL_STREAM_DRAW);
	bool UpdateData(int index, int data_size, void *buff);
};


#endif