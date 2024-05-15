// Created by Vadim on 06.05.2024.

#ifndef LAB_WORK_19_TRANSPOSE_NON_SYMMETRIC_MATRIX_H
#define LAB_WORK_19_TRANSPOSE_NON_SYMMETRIC_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../matrix/algorithms/algorithms.h"
#include "../matrix/matrix.h"
#include <assert.h>

void generate_non_symmetric_matrix(const char* filename) {
    srand(time(NULL));

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int n = rand() % 2 + 2;
    fwrite(&n, sizeof(int), 1, file);

    int amount_matrix = rand() % 3 + 1;

    for (int k = 0; k < amount_matrix; k++) {
        int matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = rand() % 100;
            }
        }
        fwrite(matrix, sizeof(int), n * n, file);
    }

    fclose(file);
}

int is_symmetric(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] != matrix[j][i])
                return 0;
    return 1;
}

void transpose(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(&matrix[i][j], &matrix[j][i]);
}

void transpose_non_symmetric_matrix(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    int n;
    if (fread(&n, sizeof(int), 1, file) != 1) {
        printf("Error when reading the order of the matrix.\n");
        fclose(file);
        return;
    }

    while(1) {
        int matrix[n][n];
        size_t read_count = fread(matrix, sizeof(int), n * n, file);
        if (read_count != n * n) {
            if (feof(file)) {
                break;
            } else {
                printf("Error reading the matrix.\n");
                break;
            }
        }

        if (!is_symmetric(n, matrix)) {
            transpose(n, matrix);
            fseek(file, -(long int)read_count * sizeof(int), SEEK_CUR);
            fwrite(matrix, sizeof(int), read_count, file);
            fseek(file, (long int)read_count * sizeof(int), SEEK_CUR); // Перемещаем указатель вперед
        }
    }

    fclose(file);
}

void print_bin_file_matrix(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int n;
    fread(&n, sizeof(int), 1, file);

    if (n == 0)
        return;

    while (!feof(file)) {
        int matrix[n][n];
        if (fread(matrix, sizeof(int), n * n, file) != n * n)
            break;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    fclose(file);
}

void test_transpose_non_symmetric_matrix_1_empty_matrix() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_8_test_1.txt";

    int n = 0;
    FILE* file = fopen(filename, "wb");

    fwrite(&n, sizeof(int), 1, file);

    fclose(file);


    file = fopen(filename, "rb");

    int res_n;
    fread(&res_n, sizeof(int), 1, file);

    fclose(file);

    assert(n == res_n);
}

void test_transpose_non_symmetric_matrix_2_one_matrices() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_8_test_2.txt";

    int n = 1;
    int x1 = 1;
    int x2 = 10;

    FILE* file = fopen(filename, "wb");

    fwrite(&n, sizeof(int), 1, file);
    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);

    fclose(file);

    int res_n, res_x1, res_x2;
    file = fopen(filename, "rb");

    fread(&res_n, sizeof(int), 1, file);
    fread(&res_x1, sizeof(int), 1, file);
    fread(&res_x2, sizeof(int), 1, file);

    fclose(file);

    assert(res_n == n);
    assert(res_x1 == x1);
    assert(res_x2 == x2);
}

void test_transpose_non_symmetric_matrix_3_symmetric_matrix() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_8_test_3.txt";

    FILE* file = fopen(filename, "wb");

    int n = 3;
    matrix m = create_matrix_from_array((int[]) {1, 0, 0,
                                                 0, 1, 0,
                                                 0, 0, 1}, 3, 3);

    fwrite(&n, sizeof(int), 1, file);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    transpose_non_symmetric_matrix(filename);

    file = fopen(filename, "rb");

    int res_n;
    fread(&res_n, sizeof(int), 1, file);
    matrix res_m = get_mem_matrix(res_n, res_n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res_m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    assert(are_two_matrices_equal(&res_m, &m));

    free_mem_matrix(&m);
    free_mem_matrix(&res_m);
}

void test_transpose_non_symmetric_matrix_4_non_symmetric_matrix() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_8_test_4.txt";

    FILE* file = fopen(filename, "wb");

    int n = 3;
    matrix m = create_matrix_from_array((int[]) {1, 2, 3,
                                                 4, 5, 6,
                                                 7, 8, 9}, 3, 3);

    fwrite(&n, sizeof(int), 1, file);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    transpose_non_symmetric_matrix(filename);

    file = fopen(filename, "rb");

    int res_n;
    fread(&res_n, sizeof(int), 1, file);
    matrix res_m = get_mem_matrix(res_n, res_n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res_m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    matrix check = create_matrix_from_array((int[]) {1, 4, 7,
                                                     2, 5, 8,
                                                     3, 6, 9}, 3, 3);

    assert(res_n == n);
    assert(are_two_matrices_equal(&res_m, &check));

    free_mem_matrix(&m);
    free_mem_matrix(&res_m);
    free_mem_matrix(&res_m);
}

void test_transpose_non_symmetric_matrix() {
    test_transpose_non_symmetric_matrix_1_empty_matrix();
    test_transpose_non_symmetric_matrix_2_one_matrices();
    test_transpose_non_symmetric_matrix_3_symmetric_matrix();
    test_transpose_non_symmetric_matrix_4_non_symmetric_matrix();
}

#endif //LAB_WORK_19_TRANSPOSE_NON_SYMMETRIC_MATRIX_H