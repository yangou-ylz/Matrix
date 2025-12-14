cmake_minimum_required(VERSION 3.15)
project(MatrixProject)


# 文件路径配置
include_directories(include)

add_executable(MatrixProject src/Matrix.cpp src/main.cpp)

