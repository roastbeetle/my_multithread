#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using std::thread;
using std::vector;
using std::lock_guard;

/// dead lock problem

void worker1(std::mutex& m1, std::mutex& m2){
    for(int i=0; i<10; i++){
        lock_guard<std::mutex> lock1(m1);
        lock_guard<std::mutex> lock2(m2);
    }
}

void worker2(std::mutex& m1, std::mutex& m2){
    for(int i=0; i<10; i++){
        lock_guard<std::mutex> lock2(m2);
        lock_guard<std::mutex> lock1(m1);
    }
}

int main(){
    std::mutex m1, m2;
   
    thread t1(worker1,std::ref(m1),std::ref(m2));
    thread t2(worker2,std::ref(m1),std::ref(m2));

    std::cout<<"end " <<std::endl;
}