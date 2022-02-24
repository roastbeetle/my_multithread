cmake_minimum_required(VERSION 3.0)
project(mthre)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(atom1 atom1.cc)
target_link_libraries(atom1 PRIVATE Threads::Threads)

add_executable(atom2 atom2.cc)
target_link_libraries(atom2 PRIVATE Threads::Threads)

add_executable(atom6 atom6.cc)
target_link_libraries(atom6 PRIVATE Threads::Threads)

add_executable(atom3 atom3.cc)
target_link_libraries(atom3 PRIVATE Threads::Threads)

add_executable(atom4 atom4.cc)
target_link_libraries(atom4 PRIVATE Threads::Threads)

add_executable(atom5 atom5.cc)
target_link_libraries(atom5 PRIVATE Threads::Threads)