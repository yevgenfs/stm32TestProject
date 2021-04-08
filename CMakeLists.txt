cmake_minimum_required(VERSION 3.15)
project(stm32_spinner_project-2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)
    
set(EXTERNAL_PROJECT_GENERATOR "MinGW Makefiles")
set(CMAKE_SH_NOT_FOUND "-DCMAKE_SH=CMAKE_SH-NOTFOUND")
set(EXTERNAL_PROJECT_COMPILER "-DCMAKE_C_COMPILER=gcc")

add_executable(stm32_spinner_project-2 Core/Src/main.c)
