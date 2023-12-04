cmake_minimum_required(VERSION 3.26)
project(ReadingLargeFiles)

set(CMAKE_CXX_STANDARD 17)

add_executable(ReadingLargeFiles main.cpp
        SaleStatistic.h
        SaleStatistic.cpp)
