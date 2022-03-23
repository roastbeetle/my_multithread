cmake_minimum_required(VERSION 3.0)
project(mthre)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(mthre1 mthre1.cc)
target_link_libraries(mthre1 PRIVATE Threads::Threads)

add_executable(mthre2 mthre2.cc)
target_link_libraries(mthre2 PRIVATE Threads::Threads)

add_executable(mthre3 mthre3.cc)
target_link_libraries(mthre3 PRIVATE Threads::Threads)

add_executable(mthre4 mthre4.cc)
target_link_libraries(mthre4 PRIVATE Threads::Threads)
