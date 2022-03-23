add_library( sig SHARED
    dispatcher.cc
    request.cc
    worker.cc
)

target_link_libraries( sig
    PRIVATE Threads::Threads
)

add_executable(main main.cc)
target_link_libraries( main sig )