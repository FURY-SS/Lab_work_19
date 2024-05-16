// Created by Vadim on 16.05.2024.

#ifndef LAB_WORK_19_FIND_MEDIAN_H
#define LAB_WORK_19_FIND_MEDIAN_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include "../matrix/matrix.h"

int cmp(const void* a, const void* b) {
    return *(const unsigned int *) a - *(const unsigned int *) b;
}

int get_median_in_area(matrix* m, const int i, const int j, const int filter) {
    int border = filter * 2 + 1;

    int *temp = (int *) malloc((border * border) * sizeof(int));

    int size = 0;
    for (int row_i = i - filter; row_i <= i + filter; row_i++)
        for (int col_j = j - filter; col_j <= j + filter; col_j++)
            if (row_i != i || col_j != j) {
                temp[size] = m->values[row_i][col_j];
                size++;
            }

    qsort(temp, size, sizeof(int), cmp);

    int result = (temp[size / 2 - 1] + temp[size / 2]) / 2;

    free(temp);

    return result;
}

void median_filter(int n, int filter, matrix m) {
    filter /= 2;

    for (int i = filter; i < n - filter; i++)
        for (int j = filter; j < n - filter; j++)
            m.values[i][j] = get_median_in_area(&m, i, j, filter);
}

void test_median_filter() {
    int n = 3;
    int filter = 3;

    matrix m = create_matrix_from_array((int[]) {10, 20, 30,
                                                 25, 35, 45,
                                                 15, 25, 35}, n, n);

    median_filter(n, filter, m);

    matrix check = create_matrix_from_array((int[]) {10, 20, 30,
                                                     25, 25, 45,
                                                     15, 25, 35}, n, n);

    assert(n == 3);
    assert(filter == 3);
    assert(are_two_matrices_equal(&m, &check));

    free_mem_matrix(&m);
    free_mem_matrix(&check);
}

#endif //LAB_WORK_19_FIND_MEDIAN_H