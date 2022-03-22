#include "dispatcher.h"

#include <iostream>
using namespace std;

// Static initialisations.
queue<AbstractRequest*> Dispatcher::requests;
queue<Worker*> Dispatcher::workers;
mutex Dispatcher::requestsMutex;
mutex Dispatcher::workersMutex;
vector<Worker*> Dispatcher::allWorkers;
vector<thread*> Dispatcher::threads;


// --- INIT ---
// 스레드에 worker 할당, request 대기
bool Dispatcher::init(int workers) {
	thread* t = 0;
	Worker* w = 0;
	for (int i = 0; i < workers; ++i) {
		w = new Worker(i);
		allWorkers.push_back(w);
		// worker 실행 및 request 대기 
		t = new thread(&Worker::run, w);
		threads.push_back(t);
	}
	
	return true;
}


// --- STOP ---
// Terminate the worker threads and clean up.
bool Dispatcher::stop() {
	for (int i = 0; i < allWorkers.size(); ++i) {
		allWorkers[i]->stop();
	}
	
	cout << "Stopped workers.\n";
	
	for (int j = 0; j < threads.size(); ++j) {
		threads[j]->join();
		
		cout << "Joined threads.\n";
	}
	
	return true;
}


// --- ADD REQUEST ---
void Dispatcher::addRequest(AbstractRequest* request) {
	workersMutex.lock();
	// workers(대기큐) 에 worker 존재 하는 경우 request 할당
	if (!workers.empty()) {
		Worker* worker = workers.front();
		worker->setRequest(request);
		condition_variable* cv;
		worker->getCondition(cv);
		cv->notify_one();
		workers.pop();
		workersMutex.unlock();
	}
	else {
		workersMutex.unlock();
		requestsMutex.lock();
		requests.push(request);
		requestsMutex.unlock();
	}
	
	
}


// --- ADD WORKER ---
// worker : run 시점에서 실행, request 대기
bool Dispatcher::addWorker(Worker* worker) {

	bool wait = true;
	requestsMutex.lock();
	// request 가 있을 경우 worker 에 할당
	if (!requests.empty()) {
		AbstractRequest* request = requests.front();
		worker->setRequest(request);
		requests.pop();
		wait = false;
		requestsMutex.unlock();
	}
	// request 없을 경우 workers(대기 큐) 에 worker 추가 
	else {
		requestsMutex.unlock();
		workersMutex.lock();
		workers.push(worker);
		workersMutex.unlock();
	}
	// 초기 Wait : True
	return wait;
}
