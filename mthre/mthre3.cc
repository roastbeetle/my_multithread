#include <iostream>
#include <thread>
#include <vector>
using std::thread;
using std::vector;

void worker(int& counter){
    for(int i=0; i<10000; i++){
        counter+=1;
    }
}
int main(){
    int counter=0;
    vector<thread> workers;
    for(int i = 0; i<4; i++){
        workers.push_back(thread(worker,std::ref(counter)));
        // race condition !
    }
    for(int i = 0; i<4; i++){
        workers[i].join();
    }
    std::cout<<"total counter : "<<counter<<std::endl;
}