#include <iostream>
#include <thread>
using std::thread;

void func1(){
    for(int i = 0; i<10; i++){
        std::cout<< "thred 1 working"<< std::endl;
    }
}

void func2(){
    for(int i = 0; i<10; i++){
        std::cout<< "thred 2 working"<< std::endl;
    }
}

void func3(){
    for(int i = 0; i<10; i++){
        std::cout<< "thred 3 working"<< std::endl;
    }
}

int main(){
    thread th1(func1);
    thread th2(func2);
    thread th3(func3);

    th1.join();
    th2.join();
    th3.join();
    
    //th1.detach();
    //th2.detach();
    //th3.detach();

    std::cout<< " ____MAIN OVER____"<<std::endl;
}