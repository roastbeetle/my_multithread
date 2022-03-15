#include "request.h"
//value : thread number

// --- PROCESS ---
void Request::process() {
	outFnc("Starting processing request " + std::to_string(value) + "...");
	
	//
}

// --- FINISH ---
void Request::finish() {
	outFnc("Finished request " + std::to_string(value));
}
