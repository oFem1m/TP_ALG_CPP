cmake_minimum_required(VERSION 3.25)
project(TP_ALG_CPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(1.1.2 dz1/1.2.cpp)
add_executable(1.2.2 dz1/2.2.cpp)
add_executable(test test.cpp)
add_executable(bin_search bin_search.cpp)
add_executable(1.3.1 dz1/3.1.cpp)
add_executable(1.4.3 dz1/4.3.cpp)
add_executable(sem1 seminars/seminar1.cpp)
add_executable(1.5.2 dz1/5.2.cpp)
add_executable(rk1.3 rk1/3.cpp)
add_executable(rk1.1 rk1/1.cpp)
add_executable(rk1.2 rk1/2.cpp)
add_executable(1.6.3 dz1/6.3.cpp)
add_executable(1.7.3 dz1/7.3.cpp)
add_executable(2.1.2 dz2/1.2.cpp)
add_executable(2.2.1 dz2/2.1.cpp)
add_executable(2.4.1 dz2/4.1.cpp)
add_executable(rk2.1 rk2/1.cpp)
add_executable(rk2.4 rk2/4.cpp)
add_executable(rk2.2 rk2/2.cpp)
add_executable(rk2.3 rk2/3.cpp)
add_executable(2.3.1 dz2/3.1.cpp)
add_executable(3.2.1 dz3/2.1.cpp)
add_executable(3.3.1 dz3/3.1.cpp)
add_executable(3.4.1 dz3/4.1.cpp)
add_executable(3.1.1 dz3/1_1/1.1.cpp
        dz3/1_1/ListGraph.cpp
        dz3/1_1/ListGraph.h
        dz3/1_1/IGraph.h
        dz3/1_1/MatrixGraph.cpp
        dz3/1_1/MatrixGraph.h
        dz3/1_1/SetGraph.cpp
        dz3/1_1/SetGraph.h
        dz3/1_1/ArcGraph.cpp
        dz3/1_1/ArcGraph.h
)
