#include <iostream>
#include <chrono>
#include <thread>

// C++14 부터 적용
using namespace std;
using namespace chrono_literals;

typedef chrono::time_point<chrono::high_resolution_clock> timepoint;

int main(){
    cout<<"STARTING SLEEP"<<endl;
    
    timepoint start = chrono::high_resolution_clock::now();
    // 정확도 측정
    this_thread::sleep_for(2s);   
    timepoint end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;
    cout<<"SLEPT FOR : " <<elapsed.count()<< "ms" <<endl;
}