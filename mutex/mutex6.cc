/*
Starting thread 1.
Thread 1 adding 2. New value: 12.
Starting thread 3.
Starting thread 2.
Starting thread 4.
Thread 4 adding 5. New value: 15.
Thread 3 adding 10. New value: 20.
Thread 2 adding 6. New value: 16.
Input: 10, Result 1: 12, Result 2: 15, Result 3: 20, Result 4: 16

1. Main   1 2 3 4
2. Start  1 3 2 4
3. Result 1 4 2 3 
--> do not syncronize

*/



#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>

using namespace std;

mutex values_mtx;
mutex cout_mtx;
vector<int> values;

int randGen(const int& min, const int& max){
	// 자신 Thread 의 범위를 가지는 static 변수 generator 생성 
    static thread_local mt19937 generator(hash<thread::id>()(this_thread::get_id()));
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}

void threadFnc(int tid) {

	cout_mtx.lock();    // 쓰기 보장 (cout 공유)
	cout << "Starting thread " << tid << ".\n";
	cout_mtx.unlock();
	
	values_mtx.lock();  // 읽기 보장 (values 공유)
	int val = values[0];
	values_mtx.unlock();
	
	int rval = randGen(0, 10);
	val += rval;
	
	cout_mtx.lock();	// 쓰기 보장 (cout 공유)
	cout << "Thread " << tid << " adding " << rval << ". New value: " << val << ".\n";
	cout_mtx.unlock();
	
	values_mtx.lock();	// 쓰기 보장 (values 공유)	
	values.push_back(val);
	values_mtx.unlock();
}

int main() {
	/// values = [10]
	values.push_back(10);
	
	thread tr1(threadFnc, 1);
	thread tr2(threadFnc, 2);
	thread tr3(threadFnc, 3);
	thread tr4(threadFnc, 4);
	
	tr1.join();
	tr2.join();
	tr3.join();
	tr4.join();
	
	cout << "Input: " << values[0] << ", Result 1: " << values[1] << ", Result 2: " << values[2] << ", Result 3: " << values[3] << ", Result 4: " << values[4] << "\n";
	
	return 1;
}
