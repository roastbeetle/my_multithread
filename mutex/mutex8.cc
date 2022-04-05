#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>

std::chrono::milliseconds interval(50);
// 글로벌 mutex : 동일 자원 공유
std::mutex mutex;
int shared_counter = 0;
int exclusive_counter = 0;

void worker0(){
    std::this_thread::sleep_for(interval);
    while(true){
        // lock을 위한 대기 없이, mutex 상태만을 판별 

        if(mutex.try_lock()){ // lock 가능 (worker1 에서 처리되고 있지 않음)
            std::cout<<"SHARED ("<<shared_counter<<")"<<std::endl;
            mutex.unlock();
            return;
        }
        else{ //lock 불가능 (worker1 에서 처리중)
            ++exclusive_counter;
            std::cout<<"EXCLUSIVE ("<<exclusive_counter<<")"<<std::endl;
            std::this_thread::sleep_for(interval);
        }
    }
}

void worker1(){
    mutex.lock();
    std::this_thread::sleep_for(7*interval);
    ++shared_counter;
    mutex.unlock();
}

int main(){
    std::thread t1(worker0);
    std::thread t2(worker1);
    t1.join();
    t2.join();
}