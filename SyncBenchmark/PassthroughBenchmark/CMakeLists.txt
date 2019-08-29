cmake_minimum_required(VERSION 3.14)
project(SyncPerformanceTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(SyncPerformanceTest
        main.cpp
        TestTime.cpp
        TestTime.h
        BenchmarkTest.cpp
        BenchmarkTest.h
        PerformanceMonitor.cpp
        PerformanceMonitor.h
        Listener.cpp Listener.h ListenerImpl.cpp ListenerImpl.h)