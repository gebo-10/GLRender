#include <VAO.h>
VAO::VAO() :id(0){ vbos.clear(); }
VAO::~VAO(){}

void VAO::Init(void){
	glGenVertexArrays(1, &id);
}
void VAO::Bind(void){
	glBindVertexArray(id);
}
void VAO::UnBind(void){
	glBindVertexArray(0);
}
int VAO::NewVBO(int data_size, void * buff, int type, int sign ){
	VBO vbo;
	Bind();
	vbo.init(data_size, buff, type, sign);

	vbos.push_back(vbo);
	return vbos.size() - 1;
}
int VAO::NewEBO(int data_size, void * buff,int type, int sign ) {
	return NewVBO(data_size,buff, type, sign);
}

bool VAO::UpdateData(int index, int data_size, void *buff)
{
	Bind();
	return vbos[index].UpdateDate(data_size,buff);
}
