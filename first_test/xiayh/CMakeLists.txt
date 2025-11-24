cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 23)





set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include_directories(include)
file(GLOB SRC
    "src/*.cpp"
)
add_executable(Test main.cpp ${SRC})
set_property(TARGET Test PROPERTY CXX_STANDARD 23)

