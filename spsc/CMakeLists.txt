cmake_minimum_required(VERSION 3.14)

set(This Spsc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENTEND_CODE ON)

set(Headers 
    vector.h
    debug.h
)

set(Sources
    main.c
    vector.c
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)
add_subdirectory(benchmark)