#ifndef _FILESYSYTEM_H
#define _FILESYSYTEM_H
#pragma once
#include<Base.hpp>
#include <WorkQueue.h>
//�ļ�ϵͳ�ļ��� http win linux anroid ios
//���ļ� �ڴ�ӳ�似��
//���߳�
//���ڹ�������
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
		//delete buff; ����������棬��Դ����ģ����ɾ��
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
		// Ҫ���������ļ���������ö����ƴ�   
		filestr.open(file_work->filename, ios::binary);
		// ��ȡfilestr��Ӧbuffer�����ָ��   
		pbuf = filestr.rdbuf();

		// ����buffer���󷽷���ȡ�ļ���С  
		size = pbuf->pubseekoff(0, ios::end, ios::in);
		pbuf->pubseekpos(0, ios::in);

		// �����ڴ�ռ�  
		buffer = new char[size+1];
		buffer[size] = 0;

		// ��ȡ�ļ�����  
		pbuf->sgetn(buffer, size);

		filestr.close();
		// �������׼���  
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