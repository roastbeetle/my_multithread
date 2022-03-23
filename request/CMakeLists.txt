cmake_minimum_required(VERSION 3.0)
project(mthre)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories( include )
add_subdirectory( src )