#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

struct Box{
    explicit Box(int num): num_things{num} {}
    // explicit : 의도적이지 않은 형변환 방지. 
    //            본 예제에서는 num 과 numthing 의 오류를 방지하고자 함

    int num_things;
    std:: mutex m;
};

void transfer(Box &from, Box &to, int num){
    // unique_lock : 소유권이 자유롭기 때문에 lock 을 좀더 유연하게 사용할 수 있음 
    // defer_lock  : 따로 lock을 명시해 주어야 함 (동시 lock 권장)
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

    // lock 을 동시에 걸어야 함 (일련적인 lock이 데드락을 야기할 수 있음 )
    std::lock(lock1, lock2);

    from.num_things -= num;
    to.num_things += num;
    std::cout<<from.num_things<< " -> " << to.num_things<<std::endl;
}

int main(){
    Box acc1(100);
    Box acc2(50);

    // std::ref : 특정 객체를 참조하는 객체 생성 &로 받을 수 있다.
    std::thread t1(transfer, std::ref(acc1),std::ref(acc2),10);
    // 객체가 유지 되므로 동일한 객체를 참조
    std::thread t2(transfer, std::ref(acc1),std::ref(acc2),5);

    t1.join();
    t2.join();

}