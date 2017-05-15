#ifndef _FILESYSYTEM_H
#define _FILESYSYTEM_H
#pragma once
#include<Base.hpp>
#include <WorkQueue.h>
//文件系统的兼容 http win linux anroid ios
//大文件 内存映射技术
//多线程
//基于工作队列
class FileWork :public Work{
public:
	string filename;
	void * buff;
	Uint32 size;
	FileWork() 
	{
		buff = NULL;
		size = 0;
	};
	~FileWork() 
	{
		cout << "end file work" << endl;
		//delete buff; 这个留到缓存，资源管理模块来删除
	};
};

class FileSystem {
public:
	WorkQueue work_queue;;
	FileSystem() 
	{
		
	};
	~FileSystem() {};

	bool Init()
	{
		auto cb = std::bind(&FileSystem::OpenFileReal, this, std::placeholders::_1);
		work_queue.Init(0, cb);
		return true;
	};

	void Update(Uint32 delta)
	{
		work_queue.DealDone();
	};

	void OpenFile(string filename, std::function<void(FileWork *) > cb)
	{
		FileWork *work=new FileWork;
		work->filename = filename;
		work->cb = [=](Work * w) {
			cb((FileWork *)w);
		};

		work_queue.AddWork(work);

	};

	FileWork * OpenFileSync(string filename)
	{
		FileWork *work = new FileWork;
		work->filename = filename;

		OpenFileReal(work);
		return work;
	};


	void OpenFileReal(Work * work)
	{
		FileWork * file_work = (FileWork *)work;
		filebuf *pbuf;
		ifstream filestr;
		long size;
		char * buffer;
		// 要读入整个文件，必须采用二进制打开   
		filestr.open(file_work->filename, ios::binary);
		// 获取filestr对应buffer对象的指针   
		pbuf = filestr.rdbuf();

		// 调用buffer对象方法获取文件大小  
		size = pbuf->pubseekoff(0, ios::end, ios::in);
		pbuf->pubseekpos(0, ios::in);

		// 分配内存空间  
		buffer = new char[size+1];
		buffer[size] = 0;

		// 获取文件内容  
		pbuf->sgetn(buffer, size);

		filestr.close();
		// 输出到标准输出  
		//cout.write(buffer, size);
		//delete[]buffer;

		file_work->buff = buffer;
		file_work->size = size;
		return ;
	};

	char * ReadTextFileSync(const char * file_name) {
		char *buffer = 0;
		std::ifstream t;
		int length;
		t.open(file_name, ios::binary);      // open input file  
		t.seekg(0, std::ios::end);    // go to the end  
		length = t.tellg();           // report location (this is the length)  
		t.seekg(0, std::ios::beg);    // go back to the beginning  
		buffer = new char[length + 1];    // allocate memory for a buffer of appropriate dimension  
		t.read(buffer, length);       // read the whole file into the buffer  
		buffer[length] = '\0';
		t.close();                    // close file handle  
		return buffer;
	}
};

#endif