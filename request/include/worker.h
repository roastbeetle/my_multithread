#pragma once
#ifndef WORKER_H
#define WORKER_H

#include "abstract_request.h"

#include <condition_variable>
#include <mutex>

using namespace std;


class Worker {
	condition_variable cv;
	mutex mtx;
	unique_lock<mutex> ulock;
	AbstractRequest* request;
	bool running;
	bool ready;
	int wnum;
	
public:
	Worker(int i) { running = true; ready = false; ulock = unique_lock<mutex>(mtx); wnum = i; }
	void run();
	void stop() { running = false; }
	// request 수락 
	void setRequest(AbstractRequest* request) { this->request = request; ready = true; }
	void getCondition(condition_variable* &cv);
};

#endif
