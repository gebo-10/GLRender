#ifndef _WORKQUEUE_H
#define _WORKQUEUE_H
#pragma once
#include<Base.hpp>
#include <queue>
//多线程
//工作队列

class Work {
public:
	int status; //完成 正在做等状态
	std::function<void(Work *) > cb;
	Work() { cout << "start work" << endl; };
	virtual  ~Work() { cout << "end work" << endl; };
};
class WorkQueue {
public:
	int status;// 是否暂停工作 什么的
	mutex lock;
	std::function<void(Work*) > process;//处理函数

	queue <Work *> work_queue;
	vector <Work *> work_list;//在update里面处理 回调 ,完成的

	WorkQueue() {};
	~WorkQueue() {};

	bool Init(int thread_num, std::function<void(Work*) > p)
	{
		process = p;
		work_list.clear();
		return true;
	};
	void DealDone()
	{
		lock.lock();
		vector <Work *> works ( work_list);
		work_list.clear();
		lock.unlock();
		for (auto itr= works.begin();itr!=works.end();itr++)
		{
			(*itr)->cb(*itr);
			delete  *itr;
		}

	};
	bool AddWork(Work * work) 
	{
		std::thread t([=]() {
			this->process(work);

			this->lock.lock();
			this->work_list.push_back(work);
			this->lock.unlock();
		});
		t.join();
		return true;
	};

	//void Stop();
};


#endif