cmake_minimum_required(VERSION 3.0)
project(mthre)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(pthread1 pthread1.cc)
target_link_libraries(pthread1 PRIVATE Threads::Threads)

add_executable(pthread2 pthread2.cc)
target_link_libraries(pthread2 PRIVATE Threads::Threads)