#ifndef VAO_H
#define VAO_H
#include<GL/glew.h>
#include<vector>
#include<VBO.hpp>
using namespace std;
class VAO
{
public:
	GLuint id;
	vector<VBO> vbos;
	VBO ebo;		//Ë÷Òý»º´æ
public:
	VAO();
	~VAO();
	void init(void);
	void bind(void);
	void unBind(void);
	int newVBO(int data_size, void * buff, int type , int sign);
	void initEBO(int data_size, void * buff);
};

VAO::VAO() :id(0){ vbos.clear(); }
VAO::~VAO(){}

void VAO::init(void){
	glGenVertexArrays(1, &id);
}
void VAO::bind(void){
	glBindVertexArray(id);
}
void VAO::unBind(void){
	glBindVertexArray(0);
}
int VAO::newVBO(int data_size, void * buff, int type = GL_ARRAY_BUFFER, int sign = GL_STATIC_DRAW){
	VBO vbo;
	bind();
	vbo.init(data_size, buff, type , sign);

	vbos.push_back(vbo);
	int count = vbos.size() -1;
	return count;
}
void VAO::initEBO(int data_size, void * buff ) {
	int type = GL_ELEMENT_ARRAY_BUFFER;
	int sign = GL_STATIC_DRAW;

	bind();
	ebo.init(data_size, buff, type, sign);
	
}

#endif