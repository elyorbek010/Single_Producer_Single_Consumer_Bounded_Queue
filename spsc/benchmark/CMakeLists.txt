cmake_minimum_required(VERSION 3.14)

set(This SpscBenchmark)

set(Sources 
    spsc_benchmark.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    Spsc
    benchmark::benchmark
)