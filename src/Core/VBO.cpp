#include <VBO.h>

VBO::VBO() :id(0), type(GL_ARRAY_BUFFER), buff_len(0), data_size(0), buff(0){}

//data_size 为字节数
void VBO::init(int data_size, void * buff, int type , int sign ){
	this->data_size = data_size;
	this->type = type;
	this->buff = buff;
	this->gpu_memery_hint = sign;
	glGenBuffers(1, &id);
	glBindBuffer(type, id);
	glBufferData(type, data_size, buff, sign);
	//glBindBuffer(type, 0);
}
void VBO::bind(void){
	glBindBuffer(type, id);
}
bool VBO::UpdateDate(int data_size, void * buff)
{
	glBindBuffer(type, id);
	glBufferSubData(type, 0, data_size, buff);
	return true;
}
VBO::~VBO(){
	//GLuint  buffers[] = { id };
	//glDeleteBuffers(1,&id); //崩溃了???
}
