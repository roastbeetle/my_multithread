#include "request.h"

// --- PROCESS ---
void Request::process(int wnum) {
	outFnc( std::to_string(wnum) + " : Starting processing request " + std::to_string(value) + "...");
}

// --- FINISH ---
void Request::finish(int wnum) {
	outFnc(std::to_string(wnum) + " : Finished request " + std::to_string(value));
}
