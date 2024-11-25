#include <iostream>
#include "task.h"
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "threadpool.h"

using namespace std;

threadpool::threadpool(int num) {
	this->thread_num = num;
	thread_queue.resize(thread_num);
	for (int i = 0; i < thread_num; i++) {
		thread_queue[i] = thread(mainworker, this);
	}
}

threadpool::~threadpool() {
	cond.notify_all();
	for (int i = 0; i < thread_num; i++) {
		if (thread_queue[i].joinable()) {
			thread_queue[i].join();
		}
	}
	cout << "end" << endl;
}

void threadpool::add(task* task) {
	unique_lock<mutex> lk(mutexpool);
	task_queue.push(task);
	cond.notify_one();
	lk.unlock();
}

void threadpool::mainworker(void* arg) {
	threadpool* pool = static_cast<threadpool*>(arg);
	while (1) {
		unique_lock<mutex> lk(pool->mutexpool);
		while (pool->task_queue.empty()) {
			pool->cond.wait(lk);
		}
		task* task = pool->task_queue.front();
		pool->task_queue.pop();
		lk.unlock();
		task->a(task->arg);
		delete task;
	}
}