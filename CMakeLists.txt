cmake_minimum_required(VERSION 3.26.4)
project(dictionary)

set(CMAKE_CXX_STANDARD 20)

add_executable(dictionary main.cpp
        ArrayList.hpp
        BaseList.hpp
        Menu.h
        Menu.cpp
        TestGenerator.cpp
        TestGenerator.hpp
        Utility.hpp
        AVLTree.hpp
        CuckooHashTable.hpp
        AVLTreeHashTable.hpp
        LinearProbingHashTable.h
)
