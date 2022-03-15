#include "worker.h"
#include "dispatcher.h"

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
			// Execute the request.
			ready = false;
			request->process();
			request->finish();
		}
		
		// Add self to Dispatcher queue and execute next request or wait.
		if (Dispatcher::addWorker(this)) {
			// Use the ready loop to deal with spurious wake-ups.
			while (!ready && running) {
				if (cv.wait_for(ulock, chrono::seconds(1)) == cv_status::timeout) {
					// We timed out, but we keep waiting unless the worker is
					// stopped by the dispatcher.
				}
			}
		}
	}
}
