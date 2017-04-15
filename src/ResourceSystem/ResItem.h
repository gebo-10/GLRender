#ifndef _RESITEM_H
#define _RESITEM_H
#pragma once
#include<Base.hpp>
enum ResType
{
	NORMAL,
	SHADER,
};
class ResItem {
public:
	string filename;
	void * buff;
	Uint32 size;
	ResItem() {
		buff = NULL;
		size = 0;
	};
	virtual ~ResItem() {
		size = 0;
		if (buff != NULL)
		{
			delete buff;
			buff = NULL;
		}
		cout << "Res delete:" << filename << endl;
	};
	virtual bool Init() { return true; };
};
typedef  shared_ptr<ResItem> ResPtr;

#endif
