cmake_minimum_required(VERSION 3.29)
project(DS_wet1_winter_2026)

set(CMAKE_CXX_STANDARD 17)

add_executable(main26.a1 main26a1.cpp
        TechSystem26a1.cpp
        TechSystem26a1.h
        AVLTree.h
        wet1util.h
        Student.h
        Course.h
        Course.cpp
        Student.cpp
)