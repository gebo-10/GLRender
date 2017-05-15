#ifndef _RESITEM_H
#define _RESITEM_H
#pragma once
#include<Base.hpp>
enum ResType
{
	RT_NORMAL,
	RT_SHADER,
	RT_TEXTURE,
	RT_MATERIAL,
};
class ResItem : public GCObject
{
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
	virtual bool LoadCallback() { return true; };
};
typedef  std::shared_ptr<ResItem> ResPtr;

#endif
