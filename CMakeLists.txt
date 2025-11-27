cmake_minimum_required(VERSION 3.10)
project("实时传感器流水线")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    add_compile_options("/utf-8")
endif()
add_executable(action 
src/main.cpp 
src/SeneorTask.cpp 
src/Taskmanager.cpp )