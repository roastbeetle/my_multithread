#include "worker.h"
#include "dispatcher.h"

// 실질 프로그램 worker
#include <chrono>

using namespace std;

// --- GET CONDITION ---
void Worker::getCondition(condition_variable* &cv) {
	cv = &(this)->cv;
}


// --- RUN ---
// Runs the worker instance.
void Worker::run() {
	while (running) {
		if (ready) {
			// request 실행
			ready = false;
			request->process(wnum);
			request->finish(wnum);
		}
		
		// request 대기 (dispatcher 에 worker 등록)
		// 초기 addWorker 리턴 : 1
		if (Dispatcher::addWorker(this)) {
			// time out 혹은 ready = true 을 대기
			while (!ready && running) { 
				if (cv.wait_for(ulock, chrono::seconds(1)) == cv_status::timeout) {
					// We timed out, but we keep waiting unless the worker is
					// stopped by the dispatcher.
				}
			}
		}
	}
}
