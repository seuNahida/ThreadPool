#pragma once
#include <iostream>
#include<string>

using namespace std;

class task {
public:
	task(string name);
	void createTask(void(*a)(void* arg),void* arg);

	string name;
	void* arg;
	void (*a)(void* arg);
};