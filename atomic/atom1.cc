#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

void worker(std::atomic<int>& counter){
    for(int i =0; i<10000; i++){
        counter++;
    }
}

int main(){
    std::atomic<int> counter(0);
    std::vector<std::thread> workers;
    if(counter.is_lock_free()){
        for(int i =0; i<4; i++){
            workers.push_back(std::thread(worker,ref(counter)));
        }
        for(int i =0; i<4; i++){
            workers[i].join();
        }
        std::cout << "counter total "<< counter << std::endl;
    }
}   