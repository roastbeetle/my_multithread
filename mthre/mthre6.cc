#include <iostream>
#include <thread>
#include <chrono>

// Thread SWAP 예제 ( ID 교환 )
using namespace std;

// 1초 대기 함수
void worker(){
    this_thread::sleep_for(chrono::seconds(1));
}

int main(){
    thread t1(worker);
    thread t2(worker);

    cout<<"thread 1 id:" <<t1.get_id()<<endl;
    cout<<"thread 2 id:" <<t2.get_id()<<endl;
    std::swap(t1,t2);
    cout<<"thread swapping.."<<endl;
    
    cout<<"thread 1 id:" <<t1.get_id()<<endl;
    cout<<"thread 2 id:" <<t2.get_id()<<endl;
    t1.swap(t2);
    cout<<"thread swapping.."<<endl;

    cout<<"thread 1 id:" <<t1.get_id()<<endl;
    cout<<"thread 2 id:" <<t2.get_id()<<endl;
    t1.join();
    t2.join();
}

