cmake_minimum_required(VERSION 3.26)
project(CrimeStatistics)

set(CMAKE_CXX_STANDARD 17)

add_executable(CrimeStatistics main.cpp
        CrimeStatistic.cpp
        CrimeStatistic.h
        makeStuffHaveNormalLineBreaks.cpp)
