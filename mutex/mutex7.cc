#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex display_mutex;
void worker(){
    thread::id this_id = this_thread::get_id();
    
    display_mutex.lock();
    cout<<"thread "<<this_id<<" sleeping"<<endl;
    display_mutex.unlock();

    this_thread::sleep_for(chrono::seconds(1));
}

int main(){
    // 정수형 thread id
    thread t1(worker);
    thread::id t1_id = t1.get_id();

    thread t2(worker);
    thread::id t2_id = t2.get_id();
    
    // 동일 메모리자원 (화면 출력) 에 대해 동일한 mutex 변수 사용 가능
    display_mutex.lock();
    cout<<"t1 id:"<<t1_id<<endl;
    cout<<"t2 id:"<<t2_id<<endl;
    display_mutex.unlock();

    t1.join();
    t2.join();
}