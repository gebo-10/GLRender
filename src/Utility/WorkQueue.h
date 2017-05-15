#ifndef _WORKQUEUE_H
#define _WORKQUEUE_H
#pragma once
#include<Base.hpp>
#include <queue>
//���߳�
//��������

class Work {
public:
	int status; //��� ��������״̬
	std::function<void(Work *) > cb;
	Work() { cout << "start work" << endl; };
	virtual  ~Work() { cout << "end work" << endl; };
};
class WorkQueue {
public:
	int status;// �Ƿ���ͣ���� ʲô��
	mutex lock;
	std::function<void(Work*) > process;//������

	queue <Work *> work_queue;
	vector <Work *> work_list;//��update���洦�� �ص� ,��ɵ�

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