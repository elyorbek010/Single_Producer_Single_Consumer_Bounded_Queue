cmake_minimum_required(VERSION 3.14)

set(This SpscTest)

set(Sources 
    spsc_tests.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    Spsc
)

gtest_discover_tests(${This})