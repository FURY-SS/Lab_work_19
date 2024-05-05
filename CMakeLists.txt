cmake_minimum_required(VERSION 3.27)
project(Lab_work_19 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_work_19 main.c
        matrix/matrix.c
        algorithms/algorithms.c
        tasks/convert_float_num.h
        vector/vector.c
        vector/vector.h
        vector/vector_void.c
        vector/vector_void.h
        string/string.c
        string/string.h)
