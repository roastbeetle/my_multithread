#include "dispatcher.h"
#include "request.h"

#include <iostream>
#include <string>
#include <csignal>
#include <thread>
#include <chrono>

using namespace std;


// Global
// sig_atomic_t : signal 의 원자적 변수로 안전성 보장
sig_atomic_t signal_caught = 0;
mutex logMutex;

void sigint_handler(int sig) {
	signal_caught = 1;
}

// 로그 출력 함수
void logFnc(string text) { 
	logMutex.lock(); 
	cout << text << "\n";
	logMutex.unlock();
}


int main() {
	// 시그널 핸들러 (sigint)
	signal(SIGINT, &sigint_handler);
	
	// 10 Worker 스레드 할당 
	// worker 대기 큐 (workers) 에 10개의 Worker 할당
	Dispatcher::init(10);	
	cout << "Initialised.\n";
	
	int cycles = 0;
	Request* rq = 0;
	while (!signal_caught && cycles < 50) {
		rq = new Request(); 
		rq->setValue(cycles);
		rq->setOutput(&logFnc);
		// 요청 대기 큐 (requests) 에 50개의 Request 할당
		Dispatcher::addRequest(rq);
		cycles++;
	}
	
	this_thread::sleep_for(chrono::seconds(5));
	
	// Cleanup.
	Dispatcher::stop();
	cout <<cycles<< "Clean-up done.\n";
	
	return 0;
}
