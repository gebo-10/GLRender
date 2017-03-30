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
	int count = vbos.size() - 1;
	return count;
}
void VAO::InitEBO(int data_size, void * buff) {
	int type = GL_ELEMENT_ARRAY_BUFFER;
	int sign = GL_STATIC_DRAW;

	Bind();
	ebo.init(data_size, buff, type, sign);

}