#include <atomic>
#include <iostream>
#include <thread>
using std::thread;

std::atomic<bool> x(false);
std::atomic<bool> y(false);
std::atomic<int> z(0);

void write_x(){ x.store(true, std::memory_order_release); }
void write_y(){ y.store(true, std::memory_order_release); }

void read_x_then_y(){
    while(!x.load(std::memory_order_acquire)){
    }
    if(y.load(std::memory_order_acquire)){
        ++z;
    }
}

void read_y_then_x(){
    while(!y.load(std::memory_order_acquire)){
    }
    if(x.load(std::memory_order_acquire)){
        ++z;
    }
}

int main(){
    thread a(write_x);
    thread b(write_y);
    thread c(read_x_then_y);
    thread d(read_y_then_x);

    a.join();
    b.join();
    c.join();
    d.join();
    std::cout<<"Z : "<< z <<std::endl;
}