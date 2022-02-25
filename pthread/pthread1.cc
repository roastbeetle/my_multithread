// POSIX 스레드 예제

#include <pthread.h> 
#include <stdlib.h> 
#include <iostream>
#include <queue>
  
#define NUM_THREADS 100

static pthread_mutex_t func_mutex = PTHREAD_MUTEX_INITIALIZER; 
static std::queue<int> arr;
 
void func(int value) { 

    // safe 하지 않음, 반드시 mutex lock
    //arr.pop();
    //std::cout << arr.front() << std::endl; 

    pthread_mutex_lock(&func_mutex);
    arr.pop();
    std::cout << arr.front() << std::endl;     
    pthread_mutex_unlock(&func_mutex); 
} 

void* worker(void* arg) { 
    int value = *((int*) arg); 
    
    func(value);
  
    return 0; 
} 

int main(int argc, char** argv) { 
    pthread_t threads[NUM_THREADS]; 
    int thread_args[NUM_THREADS]; 
    int result_code; 

    for(int i = 0; i<NUM_THREADS ; i++){
        arr.push(i);
    }

    for (unsigned int i = 0; i < NUM_THREADS; ++i) { 
        thread_args[i] = i; 
        result_code = pthread_create(&threads[i], 0, worker, (void*) &thread_args[i]); 
    } 

	for (int i = 0; i < NUM_THREADS; ++i) { 
        result_code = pthread_join(threads[i], 0); 
    } 

    exit(0); 
} 
