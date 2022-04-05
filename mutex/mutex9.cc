#include <thread>
#include <mutex>
#include <iostream>

int counter = 0;
std::mutex counter_mutex;
void worker(){
    // lock_guard : lock - unlock 해결
    std::lock_guard<std::mutex> lock(counter_mutex);
    if(counter==1)         {counter += 10;}
    else if(counter >=10)  {counter += 15;}
    else if (counter >=50) {return;       }
    else                   { ++counter;   }
    std::cout<<std::this_thread::get_id()<<" : " <<counter<<std::endl;
}

int main(){
    std::cout<<__func__<<" : "<<counter<<std::endl;
    std::thread t1(worker);
    std::thread t2(worker);
    std::thread t3(worker);
    std::thread t4(worker);
    std::thread t5(worker);
    std::thread t6(worker);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    std::cout<<__func__<<" : "<<counter<<std::endl;
}