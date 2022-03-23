#pragma once

#ifndef REQUEST_H
#define REQUEST_H

#include "abstract_request.h"
#include <string>

using namespace std;

typedef void (*logFunction)(string text);
//함수 포인터 : logFunction pA 로 선언
// 			  pA = functionA
//		  	  pA(string text) 형태로 사용

class Request : public AbstractRequest {
	int value;
	logFunction outFnc;
	
public:
	/*
	this : 객체 주소 
	ex) 컴파일러 변환 A.setValue(3) = A.setValue(A주소(this), 3)
	*/
	void setValue(int value) { this->value = value; }

	// 함수 포인터 할당
	void setOutput(logFunction fnc) { outFnc = fnc; }
	
	// wnum : Worker number
	void process(int wnum);
	void finish(int wnum);
};

#endif
