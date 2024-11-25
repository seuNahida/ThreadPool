#include<iostream>
#include "task.h"

task::task(string name) {
	this->name = name;
	this->a = nullptr;
	this->arg = nullptr;
}

void task::createTask(void(*a)(void* arg), void* arg) {
	this->a = a;
	this->arg = arg;
}