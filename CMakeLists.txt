cmake_minimum_required(VERSION 3.27)
project(Lab_work_19 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_work_19 main.c
        matrix/matrix.c
        matrix/algorithms/algorithms.c
        tasks/convert_float_num.h
        vector/vector.c
        vector/vector.h
        vector/vector_void.c
        vector/vector_void.h
        string/string.c
        string/string.h
        tasks/evaluate_expression.h
        tasks/special_word.h
        "tasks/leave_longest_word .h"
        tasks/remove_polynomial.h
        tasks/rearrange_numbers.h
        tasks/transpose_non_symmetric_matrix.h
        matrix/algorithms/algorithms.h
        tasks/get_best_team.h
        tasks/update_product.h
        tasks_20_lab/matrix_transformation.h
)
