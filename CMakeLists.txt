cmake_minimum_required(VERSION 3.23)
project(Siaod)

set(CMAKE_CXX_STANDARD 20)

add_executable(Siaod main.cpp Siaod4/RBTree.cpp Siaod4/RBTree.h Siaod4/BinF.cpp Siaod4/BinF.h Siaod4/BTree.cpp Siaod4/BTree.h)
