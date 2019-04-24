cmake_minimum_required(VERSION 3.13)
project(Generated_SP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.
        /usr)

add_executable(Generated_SP
        CargoStream.cpp
        Execution.cpp
        main.cpp
        OutputStream.cpp
        BenchMarkTesting.cpp BenchMarkTesting.h Data.h DataGenerator.cpp DataGenerator.h)

link_directories(
        /usr
)

target_link_libraries(Generated_SP rdkafka)