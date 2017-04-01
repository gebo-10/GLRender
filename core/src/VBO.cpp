#include <VBO.h>

VBO::VBO() :id(0), type(GL_ARRAY_BUFFER), buff_len(0), data_size(0), buff(0){}

//data_size Ϊ�ֽ���
void VBO::init(int data_size, void * buff, int type , int sign ){
	glGenBuffers(1, &id);
	glBindBuffer(type, id);
	glBufferData(type, data_size, buff, sign);
	//glBindBuffer(type, 0);
}
void VBO::bind(void){
	glBindBuffer(type, id);
}
VBO::~VBO(){
	//GLuint  buffers[] = { id };
	//glDeleteBuffers(1,&id); ������???
}
