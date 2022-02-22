#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using std::thread;
using std::vector;

void worker(int& result, std::mutex& m){
    for(int i=0; i<10000; i++){
        //m.lock();
        //result+=1;
        //m.unlock();
        std::lock_guard<std::mutex> lock(m);
        result += 1;
    }
}
int main(){
    int counter=0;
    std::mutex m;
    vector<thread> workers;
    for(int i = 0; i<4; i++){
        workers.push_back(thread(worker,std::ref(counter),std::ref(m)));
    }
    for(int i = 0; i<4; i++){
        workers[i].join();
    }
    std::cout<<"total counter : "<<counter<<std::endl;
}