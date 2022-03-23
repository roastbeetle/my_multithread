#pragma once // 중복 include 방지
#ifndef ABSTRACT_REQUEST_H
#define ABSTRACT_REQUEST_H


class AbstractRequest {
	
public:
	/*
	virtual : 가상 함수 
	static binding : 대부분의 함수는 컴파일에서 메모리 위치가 결정
	dynamic binding: 가상함수의 경우 런타임에서 메모리 위치가 결정 

	ex) 포인터가 참조하는 위치를 컴파일 수준에서 알 수 없음 (상속 등) 
		따라서 일반적인 static binding 의 경우 선언된 객체를 따르지만, 
		dynamic binding 으로 묶인 가상함수의 경우 실제 객체를 참조하여 함수 위치를 사용
	*/
	virtual void setValue(int value) = 0;
	virtual void process(int wnum) = 0;
	virtual void finish(int wnum) = 0;
};

#endif
