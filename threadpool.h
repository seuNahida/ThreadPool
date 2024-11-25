#pragma once
#include <iostream>
#include "task.h"
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class threadpool {
public:
	threadpool(int num);
	~threadpool();
	static void mainworker(void* arg);
	void add(task* task);

	queue<task*> task_queue;
	vector<thread> thread_queue;
	condition_variable cond;
	mutex mutexpool;
	int thread_num;
};