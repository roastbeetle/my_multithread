#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using std::thread;
using std::vector;
using std::lock_guard;

void worker1(std::mutex& m1, std::mutex& m2){
    for(int i=0; i<10; i++){
        m1.lock();
        m2.lock();
        std::cout << "WORKER 1 " << i <<std::endl;
        m2.unlock();
        m1.unlock();
    }
}

void worker2(std::mutex& m1, std::mutex& m2){
    for(int i=0; i<10; i++){
        while(true){
            m2.lock();
            if(!m1.try_lock()){ // To avoid DeadLock, use "try_lock()"
                m2.unlock();
                continue;
            }
            std::cout << "WORKER 2 " << i <<std::endl;
            m1.unlock();
            m2.unlock();
            break;
        }
    }
}

int main(){
    std::mutex m1, m2;
   
    thread t1(worker1,std::ref(m1),std::ref(m2));
    thread t2(worker2,std::ref(m1),std::ref(m2));

    t1.join();
    t2.join();
    
    std::cout<<"end"<<std::endl;
}