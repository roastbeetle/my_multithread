#include <thread>
#include <iostream>

// void : worker 의 반환은 보통 무시됨
void worker(int n, std::string t){
    std::cout<<n<<t<<std::endl;
}

int main(){
    std::string s = "Test";
    int i = 1;
    // 인자 전달 가능
    std::thread t0(worker,i,s);
    // t1으로 스레드 이동 (동시에 기존 스레드 t0 종료)
    std::thread t1(std::move(t0));
    
    // 종료 대기 join 
    t1.join();
    return 0;
}