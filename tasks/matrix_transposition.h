// Created by Vadim on 04.05.2024.

#ifndef LAB_WORK_19_MATRIX_TRANSPOSITION_H
#define LAB_WORK_19_MATRIX_TRANSPOSITION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../matrix/matrix.h"

void generate_random_matrix_file(const char* name_file, size_t n) {
    srand(time(NULL));

    FILE* file = fopen(name_file, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fprintf(file, "%lld\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", rand() %10);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

void transpose_matrix_in_file(const char* name_file) {
    FILE* file = fopen(name_file, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    size_t n;
    fscanf(file, "%lld", &n);

    matrix matrix = get_mem_matrix((int) n ,(int) n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d",&matrix.values[i][j]);

    fclose(file);

    transpose_square_matrix(&matrix);

    file = fopen(name_file, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ",matrix.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    free_mem_matrix(&matrix);
}

void test_matrix_transpose_1_one_element_matrix() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_1_test_1.txt";

    int n = 1;
    int element = 10;

    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", n);
    fprintf(file, "%d\n", element);

    fclose(file);

    transpose_matrix_in_file(filename);

    file = fopen(filename, "r");

    int n_res, element_res;
    fscanf(file, "%d\n", &n_res);
    fscanf(file, "%d\n", &element_res);

    assert(element == element_res);

    fclose(file);
}

void test_matrix_transpose_2_unit_symmetric_matrix() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_1_test_2.txt";

    int n = 3;
    matrix m = create_matrix_from_array((int[]) {1, 0, 0,
                                                 0, 1, 0,
                                                 0, 0, 1}, 3, 3);

    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", m.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);


    transpose_matrix_in_file(filename);


    int n_result;
    matrix result_m = get_mem_matrix(n, n);

    file = fopen(filename, "r");

    fscanf(file, "%d\n", &n_result);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &result_m.values[i][j]);

    fclose(file);

    assert(are_two_matrices_equal(&m, &result_m));

    free_mem_matrix(&m);
    free_mem_matrix(&result_m);
}

void test_matrix_transpose_3_matrix() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_1_test_3.txt";

    int n = 3;
    matrix m = create_matrix_from_array((int[]) {1, 2, 3,
                                                 4, 5, 6,
                                                 7, 8, 9}, 3, 3);

    matrix check_matrix = create_matrix_from_array((int[]) {1, 4, 7,
                                                            2, 5, 8,
                                                            3, 6, 9}, 3, 3);

    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", m.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);


    transpose_matrix_in_file(filename);


    int n_result;
    matrix result_m = get_mem_matrix(n, n);

    file = fopen(filename, "r");

    fscanf(file, "%d\n", &n_result);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &result_m.values[i][j]);

    fclose(file);

    assert(are_two_matrices_equal(&check_matrix, &result_m));

    free_mem_matrix(&m);
    free_mem_matrix(&result_m);
    free_mem_matrix(&check_matrix);
}


void test_matrix_transpose() {
    test_matrix_transpose_1_one_element_matrix();
    test_matrix_transpose_2_unit_symmetric_matrix();
    test_matrix_transpose_3_matrix();
}

#endif //LAB_WORK_19_MATRIX_TRANSPOSITION_H