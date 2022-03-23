#pragma once
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "abstract_request.h"
#include "worker.h"

#include <queue>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;


class Dispatcher {
	// Dispatcher : Worker, Thread 관리
 	static queue<AbstractRequest*> requests;
	static queue<Worker*> workers;
	static mutex requestsMutex;
	static mutex workersMutex;
	static vector<Worker*> allWorkers;
	static vector<thread*> threads;
	
public:
	static bool init(int workers);
	static bool stop();
	// 대기중인 worker 가 request 를 할당받음 ( 새로운 request 추가 )
	static void addRequest(AbstractRequest* request);
	// 대기중인 request 를 worker가 할당받음  ( 새로운 worker 추가 )
	static bool addWorker(Worker* worker);
};

#endif
