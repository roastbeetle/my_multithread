cmake_minimum_required(VERSION 3.0)
project(mthre)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(mutex1 mutex1.cc)
target_link_libraries(mutex1 PRIVATE Threads::Threads)

add_executable(mutex2 mutex2.cc)
target_link_libraries(mutex2 PRIVATE Threads::Threads

add_executable(mutex3 mutex3.cc)
target_link_libraries(mutex3 PRIVATE Threads::Threads)

add_executable(mutex4 mutex4.cc)
target_link_libraries(mutex4 PRIVATE Threads::Threads)

add_executable(mutex5 mutex5.cc)
target_link_libraries(mutex5 PRIVATE Threads::Threads)

add_executable(mutex6 mutex6.cc)
target_link_libraries(mutex6 PRIVATE Threads::Threads)