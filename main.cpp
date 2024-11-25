#include <iostream>
#include <vector>
#include "task.h"
#include <string>
#include "threadpool.h"

using namespace std;

void function(void* n);
vector<task*>task_list;

int main() {
	long* t = new long;
	*t = 10000000000000;
	task_list.resize(20);
	for (int i = 0; i < 20; i++) {
		task_list[i] = new task(to_string(i));
		task_list[i]->createTask(function, t);
	}
	threadpool pool(4);
	for (int i = 0; i < 20; i++) {
		pool.add(task_list[i]);
	}
	return 0;
}

void function(void* n) {
	int* t = static_cast<int*>(n);
	long long int result = 1;
	for (int i = 1; i <= *t; i++) {
		result += i;
	}
	cout << result << endl;
}