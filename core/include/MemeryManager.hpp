#ifndef MEMORY_H
#define MEMORY_H
#include <stdlib.h>
#include<memory.h>

class Buff
{
public:
	int buff_len;
	int data_size;
	void * data;

public:
	Buff();
	Buff(int size, int data_size, char * data);
	~Buff();

	void Resize(int size, int data_size, char * data);

private:

};
Buff::Buff() : buff_len(0), data_size(0), data(NULL){

}
Buff::Buff(int size, int data_size = 0, char * userdata = NULL) : buff_len(size), data_size(data_size), data(NULL){
	data = malloc(size);
	if (data_size != 0 && data != NULL){
		memcpy(data, userdata, data_size);
	}
}
Buff::~Buff(){
	if (data != NULL){
		free(data);
	}
}
void Buff::Resize(int size, int data_size = 0, char * userdata = NULL){
	if (data != NULL){
		free(data);
		buff_len = 0;
		data_size = 0;
		data = NULL;
	}
	data = malloc(size);
	if (data_size != 0 && data != NULL){
		memcpy(data, userdata, data_size);
	}
}
#endif